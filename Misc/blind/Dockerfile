FROM debian:buster-slim

RUN apt update
RUN apt install socat -y

RUN mkdir /ctf
COPY start.sh /ctf/start.sh
COPY exec.sh /ctf/exec.sh
COPY flag.txt /ctf/flag.txt

RUN useradd ctfuser -d /ctf
RUN chown ctfuser:ctfuser /ctf/flag.txt

EXPOSE 3424

ENTRYPOINT ["bash","/ctf/start.sh"]