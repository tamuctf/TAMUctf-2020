FROM debian:buster-slim as build

RUN apt update; apt -y install build-essential

COPY troll.c /tmp/troll.c
RUN gcc -o /tmp/troll -fno-stack-protector /tmp/troll.c

FROM debian:buster-slim

env DEBIAN_FRONTEND="noninteractive"

RUN apt-get update && apt-get install socat -y

RUN groupadd ctf

RUN mkdir /pwn

COPY --from=build /tmp/troll /pwn/troll
COPY flag.txt /pwn/flag.txt
COPY start.sh /pwn/start.sh

RUN useradd -G ctf --home=/pwn pwnuser

RUN chown -R pwnuser /pwn
RUN chmod -R 555 /pwn

EXPOSE 4765

ENTRYPOINT ["/pwn/start.sh"]
