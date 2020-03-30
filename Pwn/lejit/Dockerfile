FROM rustlang/rust:nightly-slim as build

RUN USER=root cargo new --bin lejit
WORKDIR /lejit

COPY lejit/Cargo.lock ./Cargo.lock
COPY lejit/Cargo.toml ./Cargo.toml

RUN cargo build --release
RUN rm src/*.rs

COPY lejit/src/main.rs ./src/main.rs

RUN rm ./target/release/deps/lejit*
RUN cargo build --release

FROM debian:buster-slim
MAINTAINER Addison Crump "addisoncrump@tamu.edu"

RUN apt update; apt -y --autoremove full-upgrade; apt -y install socat
RUN apt-get autoremove
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

COPY --from=build /lejit/target/release/lejit /usr/bin/lejit
COPY flag.txt /root/flag.txt

EXPOSE 31337

CMD ["/bin/bash", "-c", "exec socat -d -d TCP-LISTEN:31337,reuseaddr,fork EXEC:/usr/bin/lejit,stderr"]
