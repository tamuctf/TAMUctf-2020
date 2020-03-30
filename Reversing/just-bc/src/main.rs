use std::error::Error;
use std::fs::File;
use std::io::Read;

use tokio;
use tokio::io::BufReader;
use tokio::net::TcpListener;
use tokio::prelude::*;

fn confirm(attempt: &String) -> bool {
    let password = include_str!("../password.txt").to_string();

    attempt.eq(&password)
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn Error>> {
    let addr = "0.0.0.0:4932";
    let mut listener = TcpListener::bind(addr).await?;

    loop {
        let mut socket = listener.accept().await?.0;

        tokio::spawn(async move {
            let (rsocket, mut wsocket) = socket.split();
            let mut reader = BufReader::new(rsocket);
            loop {
                wsocket
                    .write(b"Password: ")
                    .await
                    .expect("failed to write data to socket");

                let mut attempt = String::new();
                reader
                    .read_line(&mut attempt)
                    .await
                    .expect("couldn't read from input stream");
                attempt.pop().unwrap(); // remove that pesky newline
                println!("Captured attempt: {}", attempt);

                let mut resp = String::new();
                if confirm(&attempt) {
                    File::open("/flag.txt")
                        .expect("flag.txt wasn't found")
                        .read_to_string(&mut resp)
                        .expect("flag.txt wasn't readable");
                } else {
                    resp += "lmao nice try, but that's not it";
                }
                resp.push('\n');

                wsocket
                    .write(resp.as_bytes())
                    .await
                    .expect("failed to write data to socket");
            }
        });
    }
}
