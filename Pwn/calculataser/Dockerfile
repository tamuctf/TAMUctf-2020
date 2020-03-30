FROM rust:slim as build

RUN USER=root cargo new --bin calculataser
WORKDIR /calculataser

COPY server/Cargo.lock ./Cargo.lock
COPY server/Cargo.toml ./Cargo.toml

RUN cargo build --release
RUN rm src/*.rs

COPY server/src ./src

RUN rm ./target/release/deps/calculataser*
RUN cargo build --release

FROM debian:buster-slim
MAINTAINER Addison Crump "addisoncrump@tamu.edu"

RUN apt update; apt -y --autoremove full-upgrade; apt -y install bc libtinfo5 wget
RUN wget http://snapshot.debian.org/archive/debian/20130101T091755Z/pool/main/b/bash/bash_4.2%2Bdfsg-0.1_amd64.deb -O /tmp/bash_4.2+dfsg-0.1_amd64.deb && \
 dpkg -i /tmp/bash_4.2+dfsg-0.1_amd64.deb
RUN apt-get autoremove
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# copy the build artifact from the build stage
COPY --from=build /calculataser/target/release/calculataser_server /usr/bin/calculataser
COPY flag.txt /root/flag.txt

EXPOSE 3012

# set the startup command to run your binary
CMD ["/usr/bin/calculataser"]
