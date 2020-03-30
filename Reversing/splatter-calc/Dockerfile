FROM rust:slim as build

RUN USER=root cargo new --bin splatter-calc
WORKDIR /splatter-calc

COPY Cargo.lock ./Cargo.lock
COPY Cargo.toml ./Cargo.toml

COPY src ./src

# we need nightly for function "references", still experimental
RUN rustup toolchain add nightly-x86_64-unknown-linux-gnu
RUN cargo +nightly build --release

FROM debian:buster-slim
MAINTAINER Addison Crump "addisoncrump@tamu.edu"

RUN apt update; apt -y --autoremove full-upgrade
RUN apt -y install socat

# copy the build artifact from the build stage
COPY --from=build /splatter-calc/target/release/splatter-calc /usr/bin/splatter-calc
COPY start.sh /usr/bin/server
COPY flag.txt /root/flag.txt

WORKDIR /root

EXPOSE 60032

# set the startup command to run your binary
CMD ["/usr/bin/server"]