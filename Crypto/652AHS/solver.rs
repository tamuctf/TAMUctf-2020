use std::io::prelude::*;
use std::net::TcpStream;
use std::io::BufReader;
use std::io::LineWriter;
use std::error::Error;
use std::time::Instant;

fn answer_questions(reader: &mut BufReader<&TcpStream>, writer: &mut LineWriter<&TcpStream>, results: &mut [u128], answers: &[&[u8]]) -> Result<(), Box<dyn Error>> {
    let mut line = String::new();
    results.iter_mut().map(|x| *x = 0).count();

    // clear the existing results
    for _ in 0..5 {
        reader.read_line(&mut line)?;
    }
    line.clear();

    writer.write_all("2\n".as_bytes())?;

    for _ in 0..4 {
        reader.read_line(&mut line)?;
        line.clear();
    }

    reader.read_line(&mut line)?;
    for i in 0..20usize {
        line.clear();
        writer.write_all(answers[i])?;
        let now = Instant::now();
        reader.read_line(&mut line)?;
        let time = now.elapsed().as_micros();
        results[i] += time;
    }
    println!("{}", line.trim());
    Ok(())
}

fn main() -> Result<(), Box<dyn Error>> {
    let stream = TcpStream::connect("172.17.0.2:7393")?;
    let mut reader = BufReader::new(&stream);
    let mut writer = LineWriter::new(&stream);
    let mut answers = ["No\n".as_bytes(); 20];
    let mut results = [0; 20];

    answer_questions(&mut reader, &mut writer, &mut results, &["No\n".as_bytes(); 20])?;
    let no = results[0];
    answer_questions(&mut reader, &mut writer, &mut results, &["Yes\n".as_bytes(); 20])?;

    let baseline_split = (no + results[0]) / 2;

    let mut index = 0usize;
    let mut results = [0; 20];
    while index < answers.len() {
        answer_questions(&mut reader, &mut writer, &mut results, &answers)?;
        while index < answers.len() && baseline_split < results[index] {
            index += 1;
        }
        if index == answers.len() {
            break;
        }
        answers[index] = "Yes\n".as_bytes();
        println!("Current results: {:?}", results)
    }

    writer.write_all("lmao\n".as_bytes())?;
    let mut line = String::new();
    reader.read_line(&mut line)?;
    println!("{}", line.trim());

    Ok(())
}
