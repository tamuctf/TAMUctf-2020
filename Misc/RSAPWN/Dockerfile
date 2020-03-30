FROM alpine

RUN apk --no-cache add socat python3
RUN addgroup ctf
RUN mkdir /misc
RUN adduser -G ctf --home=/misc --disabled-password ctfuser

COPY server.py /misc/server.py
COPY flag.txt /misc/flag.txt
COPY start.sh /misc/start.sh

RUN chown -R ctfuser /misc

EXPOSE 8573

ENTRYPOINT ["/misc/start.sh"]
