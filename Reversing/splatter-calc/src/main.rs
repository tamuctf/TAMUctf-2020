#![feature(fn_traits)]

use std::fs::read_to_string;

use randomize::lcg64;
use std::io::{stdin, stdout, BufRead, Write};

fn identity(res: u64, _state: u64) -> u64 { res }

fn plus(res: u64, state: u64) -> u64 { res.wrapping_add(state) }

fn minus(res: u64, state: u64) -> u64 { res.wrapping_sub(state) }

fn mult(res: u64, state: u64) -> u64 { res.wrapping_mul(state as u64) }

fn square(res: u64, _state: u64) -> u64 { res.wrapping_mul(res) }

fn lshift(res: u64, state: u64) -> u64 { res.wrapping_shl((state % 64) as u32) }

fn rshift(res: u64, state: u64) -> u64 { res.wrapping_shr((state % 64) as u32) }

fn xor(res: u64, state: u64) -> u64 { res ^ (state as u64) }

fn splattercalc(mut res: u64, mut state: u64, functions: &[&dyn Fn(u64, u64) -> u64; 8]) -> (u64, u64) {
    for _ in 0..8 {
        res = functions[(state % 8) as usize].call((res, state));
//        println!("{} => {}", state % 8, res);
        state = lcg64(state, 35423441123, 9835982734);
    }

    return (res, state);
}

fn main() {
    let functions: [&dyn Fn(u64, u64) -> u64; 8] = [
        &identity,
        &plus,
        &minus,
        &mult,
        &square,
        &lshift,
        &rshift,
        &xor
    ];

    print!("Please enter an initial rng: ");
    stdout().lock().flush().unwrap();
    let state = stdin().lock().lines().next().unwrap().unwrap().trim().parse::<u64>().unwrap_or_else(|_| {
        println!("Couldn't read a 64-bit integer from input, defaulting to 0...");
        0
    });

    match splattercalc(0xcafebabe, state, &functions) {
        (12456643129164290182, 5124507482426903457) => println!("{}", read_to_string("flag.txt").unwrap()),
        (res, state) => println!("Oops, you didn't guess the right number. You got {} with final state {}", res, state)
    }

}
