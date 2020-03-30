FROM alpine

RUN apk --no-cache add socat python

RUN addgroup ctf

RUN mkdir /crypto

RUN adduser -G ctf --home=/crypto --disabled-password cryptouser

COPY game.py /crypto/game.py
COPY flag.txt /crypto/flag.txt
COPY start.sh /crypto/start.sh
COPY key.txt /crypto/key.txt

RUN chown -R cryptouser /crypto

EXPOSE 8812

ENTRYPOINT ["/crypto/start.sh"]
