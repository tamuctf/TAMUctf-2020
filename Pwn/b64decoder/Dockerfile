FROM debian:bullseye-slim as build

RUN apt update; apt -y install build-essential gcc-multilib

COPY b64decoder.c /tmp/b64decoder.c
RUN gcc -o /tmp/b64decoder -Wl,-z,norelro -no-pie -m32 /tmp/b64decoder.c

FROM debian:buster-slim

env DEBIAN_FRONTEND="noninteractive"

RUN apt-get update && apt-get install socat -y

RUN dpkg --add-architecture i386; apt update; apt install -y libc6:i386

RUN groupadd ctf

RUN mkdir /pwn

COPY --from=build /tmp/b64decoder /pwn/b64decoder
COPY flag.txt /pwn/flag.txt
COPY start.sh /pwn/start.sh

RUN useradd -G ctf --home=/pwn pwnuser

RUN chown -R pwnuser /pwn
RUN chmod -R 555 /pwn

EXPOSE 2783

ENTRYPOINT ["/pwn/start.sh"]
