// This is largely based off of the work by the dynasm-s developers:
// https://github.com/CensoredUsername/dynasm-rs
// This software is licensed under MPL2.0. Modifications implemented
// by the TAMUctf development team.

#![feature(proc_macro_hygiene)]

use dynasm::dynasm;
use dynasmrt::{AssemblyOffset, DynasmApi, DynasmLabelApi, ExecutableBuffer};

use itertools::multipeek;
use itertools::Itertools;

use std::io::{stdin, stdout, BufRead, BufReader, BufWriter, Read, Write};
use std::mem;
use std::slice;
use std::u8;

use std::ffi::c_void;
use std::os::raw::c_uchar;
use std::error::Error;

const TAPE_SIZE: usize = (30000 / 4096 + 1) * 4096;

macro_rules! prologue {
    ($ops:ident) => {{
        let start = $ops.offset();
        dynasm!($ops
            ; sub rsp, 0x28
            ; mov [rsp + 0x30], rcx
            ; mov [rsp + 0x40], r8
            ; mov [rsp + 0x48], r9
        );
        start
    }};
}

macro_rules! epilogue {
    ($ops:ident, $e:expr) => {dynasm!($ops
        ; mov retval, $e
        ; add rsp, 0x28
        ; ret
    );};
}

macro_rules! call_extern {
    ($ops:ident, $addr:expr) => {dynasm!($ops
        ; mov [rsp + 0x30], rdi
        ; mov [rsp + 0x38], rsi
        ; mov [rsp + 0x40], rdx
        ; mov [rsp + 0x48], rcx
        ; mov rax, QWORD $addr as _
        ; call rax
        ; mov rdi, [rsp + 0x30]
        ; mov rsi, [rsp + 0x38]
        ; mov rdx,  [rsp + 0x40]
        ; mov rcx,  [rsp + 0x48]
    );};
}

struct Program<'a> {
    code: ExecutableBuffer,
    start: *const c_uchar,
    pub input: Box<dyn BufRead + 'a>,
    pub output: Box<dyn Write + 'a>,
    tape_start: AssemblyOffset,
}

impl<'a> Program<'a> {
    fn new(
        input: Box<dyn BufRead + 'a>,
        output: Box<dyn Write + 'a>,
        program: &[u8],
    ) -> Result<Program<'a>, &'static str> {
        let mut ops = dynasmrt::x64::Assembler::new().unwrap();
        let mut loops = Vec::new();
        let mut code = multipeek(program.iter().cloned());

        dynasm!(ops
            ; .arch x64
            ; .alias a_program, rdi
            ; .alias a_current, rsi
            ; .alias a_begin, rdx
            ; .alias a_end, rcx
            ; .alias retval, rax
        );

        let start: AssemblyOffset = prologue!(ops);

        while let Some(c) = code.next() {
            match c {
                b'<' => {
                    let amount = code.take_while_ref(|x| *x == b'<').count() + 1;
                    dynasm!(ops
                        ; sub a_current, (amount % TAPE_SIZE) as _
                        ; cmp a_current, a_begin
                        ; jae >wrap
                        ; add a_current, TAPE_SIZE as _
                        ;wrap:
                    );
                }
                b'>' => {
                    let amount = code.take_while_ref(|x| *x == b'>').count() + 1;
                    dynasm!(ops
                        ; add a_current, (amount % TAPE_SIZE) as _
                        ; cmp a_current, a_end
                        ; jb >wrap
                        ; sub a_current, TAPE_SIZE as _
                        ;wrap:
                    );
                }
                b'+' => {
                    let amount = code.take_while_ref(|x| *x == b'+').count() + 1;
                    if amount > u8::MAX as usize {
                        return Err("An overflow occurred");
                    }
                    dynasm!(ops
                        ; add BYTE [a_current], amount as _
                    );
                }
                b'-' => {
                    let amount = code.take_while_ref(|x| *x == b'-').count() + 1;
                    if amount > u8::MAX as usize {
                        return Err("An overflow occurred");
                    }
                    dynasm!(ops
                        ; sub BYTE [a_current], amount as _
                    );
                }
                b',' => {
                    dynasm!(ops
                        ;; call_extern!(ops, Program::getchar)
                        ; cmp al, 0
                        ; jnz ->io_failure
                    );
                }
                b'.' => {
                    dynasm!(ops
                        ;; call_extern!(ops, Program::putchar)
                        ; cmp al, 0
                        ; jnz ->io_failure
                    );
                }
                b'[' => {
                    let first = code.peek() == Some(&b'-');
                    if first && code.peek() == Some(&b']') {
                        code.next();
                        code.next();
                        dynasm!(ops
                            ; mov BYTE [a_current], 0
                        );
                    } else {
                        let backward_label = ops.new_dynamic_label();
                        let forward_label = ops.new_dynamic_label();
                        loops.push((backward_label, forward_label));
                        dynasm!(ops
                            ; cmp BYTE [a_current], 0
                            ; jz =>forward_label
                            ;=>backward_label
                        );
                    }
                }
                b']' => {
                    if let Some((backward_label, forward_label)) = loops.pop() {
                        dynasm!(ops
                            ; cmp BYTE [a_current], 0
                            ; jnz =>backward_label
                            ;=>forward_label
                        );
                    } else {
                        return Err("] without matching [");
                    }
                }
                _ => (),
            }
        }
        if loops.len() != 0 {
            return Err("[ without matching ]");
        }

        dynasm!(ops
            ;; epilogue!(ops, 0)
            ;->io_failure:
            ;; epilogue!(ops, 1)
        );

        let size = ops.offset();

        for _ in 0..TAPE_SIZE {
            dynasm!(ops
                ; nop
            );
        }

        let code = ops.finalize().unwrap();
        unsafe {
            libc::mprotect(
                code.ptr(AssemblyOffset(0)) as *mut c_void,
                code.size(),
                0b111,
            );
            libc::memset(
                code.ptr(size) as *mut c_void,
                0,
                code.ptr(AssemblyOffset(0)).offset(code.size() as isize) as usize
                    - code.ptr(size) as usize,
            );
        };
        Ok(Program {
            start: code.ptr(start),
            code,
            input,
            output,
            tape_start: size,
        })
    }

    unsafe extern "C" fn getchar(program: *mut Program, cell: *mut u8) -> u8 {
        let program = &mut *program;
        let err = program.output.flush().is_err();
        (program
            .input
            .read_exact(slice::from_raw_parts_mut(cell, 1))
            .is_err()
            || err) as u8
    }

    unsafe extern "C" fn putchar(program: *mut Program, cell: *mut u8) -> u8 {
        let program = &mut *program;
        program
            .output
            .write_all(slice::from_raw_parts(cell, 1))
            .is_err() as u8
    }

    fn run(self) -> Result<(), &'static str> {
        let f: extern "C" fn(*mut Program, *mut u8, *const u8, *const u8) -> u8 =
            unsafe { mem::transmute(self.start) };
        let tape_start = unsafe { self.code.ptr(AssemblyOffset(0)).offset((self.tape_start.0) as isize) as *mut c_uchar };
        let start = self.code.ptr(AssemblyOffset(0));
        let end = unsafe { start.offset(self.code.size() as isize) };
        let res = f(Box::new(self).as_mut(), tape_start, start, end);
        if res == 0 {
            Ok(())
        } else if res == 1 {
            Err("IO error")
        } else {
            panic!("Unknown error code");
        }
    }
}

fn main() -> Result<(), Box<dyn Error>> {
    println!("Welcome to the LeJIT brainf*ck shell!");
    loop {
        print!("bf$ ");
        stdout().lock().flush()?;
        let mut buf = Vec::new();
        if let Err(_) = stdin().lock().read_until(b'\n', &mut buf) {
            panic!("Failed to read from stdin.");
        } else if buf.is_empty() {
            return Ok(());
        }

        let program = match Program::new(
            Box::new(BufReader::new(stdin())),
            Box::new(BufWriter::new(stdout())),
            &buf,
        ) {
            Ok(p) => p,
            Err(e) => {
                panic!("brainf*ck compilation failed: {}", e);
            }
        };
        if let Err(e) = program.run() {
            panic!("brainf*ck execution failed: {}", e);
        }

        println!();
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::io::{BufReader, BufWriter};
    use std::error::Error;

    fn run_program(buf: &[u8], input: &[u8], output: &mut Vec<u8>) {
        let program = match Program::new(
            Box::new(BufReader::new(input)),
            Box::new(BufWriter::new(output)),
            &buf,
        ) {
            Ok(p) => p,
            Err(e) => {
                panic!("Couldn't build the program: {}", e)
            }
        };
        if let Err(e) = program.run() {
            panic!("Program encountered a problem while running: {}", e)
        }
    }

    #[test]
    fn hello_world() -> Result<(), Box<dyn Error>> {
        let buf = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.".as_bytes();
        let input = vec![];
        let mut output = vec![];

        run_program(buf, input.as_slice(), &mut output);

        assert_eq!(String::from_utf8(output)?, "Hello World!\n");
        Ok(())
    }

    #[test]
    fn wrap_around_right() -> Result<(), Box<dyn Error>> {
        let buf = &['>' as u8; 35000];
        let input = vec![];
        let mut output = vec![];

        run_program(buf, input.as_slice(), &mut output);

        Ok(())
    }

    #[test]
    fn wrap_around_left() -> Result<(), Box<dyn Error>> {
        let buf = &['<' as u8; 35000];
        let input = vec![];
        let mut output = vec![];

        run_program(buf, input.as_slice(), &mut output);

        Ok(())
    }

    #[test]
    fn cat() -> Result<(), Box<dyn Error>> {
        let buf = ",[.,]".as_bytes();
        let input = "Hello World!\n\0".as_bytes();
        let mut output = vec![];

        run_program(buf, input, &mut output);

        assert_eq!(String::from_utf8(output)?, "Hello World!\n");
        Ok(())
    }
}
