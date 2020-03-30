FROM debian:buster-slim as build

RUN apt-get update -y; apt-get install build-essential -y;

RUN mkdir /angrmanagement
WORKDIR /angrmanagement
COPY angrmanagement.c .
RUN gcc angrmanagement.c -o angrmanagement -lm

FROM ubuntu:latest

env DEBIAN_FRONTEND="noninteractive"

RUN apt-get update && apt-get install socat -y

COPY --from=build /angrmanagement/angrmanagement /angrmanagement/angrmanagement
COPY flag.txt /angrmanagement/flag.txt
COPY start.sh /angrmanagement/start.sh

RUN groupadd ctf
RUN useradd -G ctf --home=/angrmanagement angrmanagement

RUN chown -R angrmanagement /angrmanagement
RUN chmod -R 555 /angrmanagement

EXPOSE 4322

ENTRYPOINT ["bash", "angrmanagement/start.sh"]
