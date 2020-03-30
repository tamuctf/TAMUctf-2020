use std::io::Read;
use std::error::Error;

fn main() -> Result<(), Box<dyn Error>> {
    let mut key = vec!['g' as u8, 'i' as u8, 'g' as u8, 'e' as u8, 'm' as u8, '{' as u8];
    let mut index = 0;
    for byte in std::io::stdin().lock().bytes() {
        key[index] = key[index] ^ byte?;
        index += 1;
        if index == key.len() {
            break;
        }
    }
    index = 0;
    print!("gigem{{");
    for byte in std::io::stdin().lock().bytes() {
        print!("{}", (key[index] ^ byte?) as char);
        index = (index + 1) % key.len();
    }
    println!();
    Ok(())
}
