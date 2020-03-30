FROM ubuntu:latest

env DEBIAN_FRONTEND="noninteractive"


RUN apt-get update && apt-get install socat -y

RUN groupadd ctf


RUN mkdir /pwn

COPY echoasaservice /pwn/echoasaservice
COPY flag.txt /pwn/flag.txt
COPY start.sh /pwn/start.sh

RUN useradd -G ctf --home=/pwn pwnuser

RUN chown -R pwnuser /pwn
RUN chmod -R 555 /pwn

EXPOSE 4251

ENTRYPOINT ["/pwn/start.sh"]
