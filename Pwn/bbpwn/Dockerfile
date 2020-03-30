FROM i386/ubuntu:latest

env DEBIAN_FRONTEND="noninteractive"


RUN apt-get update && apt-get install socat -y

RUN groupadd ctf


RUN mkdir /pwn

COPY bbpwn /pwn/bbpwn
COPY flag.txt /pwn/flag.txt
COPY entry.sh /pwn/entry.sh

RUN useradd -G ctf --home=/pwn pwnuser

RUN chown -R pwnuser /pwn
RUN chmod -R 555 /pwn

EXPOSE 4252

ENTRYPOINT ["/pwn/entry.sh"]
