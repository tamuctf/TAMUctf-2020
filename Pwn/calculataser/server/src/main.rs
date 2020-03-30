extern crate ws;

use std::io::{Write, stdout};
use std::process::{Command, Stdio};
use std::str;

use ws::{Error, Handler, listen, Message, Request, Response, Result, Sender};

struct Server {
    out: Sender,
    line_limit: String,
}

impl Handler for Server {
    fn on_message(&mut self, msg: Message) -> Result<()> {
        print!("{}", msg.as_text()?);
        stdout().flush()?;

        let mut child = Command::new("bash").arg("-c").arg("bc")
            .env("BC_LINE_LENGTH", self.line_limit.as_str())
            .stdin(Stdio::piped())
            .stdout(Stdio::piped())
            .spawn()
            .ok().expect("failed to spawn process");

        child.stdin.as_mut().unwrap().write_all(msg.into_data().as_ref())?;

        let output = child.wait_with_output()?.stdout;
        self.out.send(output)
    }

    fn on_error(&mut self, err: Error) {
        println!("The server encountered an error: {:?}", err);
    }

    fn on_request(&mut self, req: &Request) -> Result<Response> {
        self.line_limit = str::from_utf8(req.header("BC_LINE_LENGTH").unwrap_or("100".as_bytes().to_vec().as_ref()))?.parse().unwrap();
        Response::from_request(req)
    }
}

fn main() {
    listen("0.0.0.0:3012", |out| { Server { out, line_limit: "100".parse().unwrap() } }).unwrap()
}