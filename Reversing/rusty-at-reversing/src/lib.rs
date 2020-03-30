#![feature(lang_items)]
#![no_std]

use core::panic::PanicInfo;

static INIT_XOR: u8 = (2020 & 255) as u8;

#[no_mangle]
fn encrypt(enc: &mut [u8; 28]) {
    let mut prev = INIT_XOR;
    let mut i = 0;
    loop { // required to prevent LLVM unrolling
        enc[i] = prev ^ enc[i];
        prev = enc[i];
        i += 1;
        if i == 28 { break; }
    }
}

#[no_mangle]
fn decrypt(enc: &mut [u8; 28]) {
    let mut prev: u8;
    let mut curr = INIT_XOR;
    let mut i = 0;
    loop { // required to prevent LLVM unrolling
        prev = curr;
        curr = enc[i];
        enc[i] = prev ^ enc[i];
        i += 1;
        if i == 28 { break; }
    }
}

#[no_mangle]
fn get_flag() -> [u8; 28] {
    let mut flag: [u8; 28] = [131, 234, 141, 232, 133, 254, 147, 225, 190, 205, 185, 216, 170, 193, 158, 247, 168, 206, 171, 206, 162, 253, 143, 250, 137, 253, 132, 249];
    decrypt(&mut flag);
    flag
}

#[panic_handler]
fn panic_handler(_info: &PanicInfo) -> ! { loop {} }

#[lang = "eh_personality"]
extern "C" fn eh_personality() {}

//#[lang = "panic_fmt"]
//extern "C" fn panic_fmt() -> ! { loop {} }

#[cfg(test)]
mod tests {
    use super::*;

    static FLAG: &'static str = "gigem{mr_stark_i_feel_rusty}";

//    #[test]
//    fn encrypt_flag() {
//        let mut flag_arr = [0; 28];
//        flag_arr.copy_from_slice(FLAG.as_bytes());
//        encrypt(&mut flag_arr);
//        println!("{:?}", flag_arr);
//    }

    #[test]
    fn encrypt_decrypt_match() {
        let mut flag_arr = [0; 28];
        flag_arr.copy_from_slice(FLAG.as_bytes());
        encrypt(&mut flag_arr);
        decrypt(&mut flag_arr);
        for i in 0..flag_arr.len() {
            assert_eq!(FLAG.as_bytes()[i], flag_arr[i]);
        }
    }

    #[test]
    fn get_flag_match() {
        let flag_arr = get_flag();
        for i in 0..flag_arr.len() {
            assert_eq!(FLAG.as_bytes()[i], flag_arr[i]);
        }
    }
}
