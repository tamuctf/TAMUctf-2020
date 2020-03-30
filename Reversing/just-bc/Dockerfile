FROM rust as build

WORKDIR /tmp
RUN USER=root cargo init
COPY Cargo.toml /tmp/Cargo.toml
COPY Cargo.lock /tmp/Cargo.lock
RUN cargo build --release

COPY src/main.rs /tmp/src/main.rs
COPY password.txt /tmp/password.txt
RUN cargo clean
RUN cargo build --release

FROM debian:buster-slim

COPY --from=build /tmp/target/release/just-bc /usr/bin/just-bc
COPY flag.txt /flag.txt

EXPOSE 4932

ENTRYPOINT ["/usr/bin/just-bc"]
