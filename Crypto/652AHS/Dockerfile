FROM alpine

RUN apk --no-cache add socat python3

RUN addgroup ctf

RUN mkdir /crypto

RUN adduser --disabled-password -G ctf --home=/crypto cryptouser

COPY server.py /crypto/server.py
COPY flag.txt /crypto/flag.txt
COPY start.sh /crypto/start.sh
COPY questions.txt /crypto/questions.txt
COPY security_hashes.txt /crypto/security_hashes.txt
COPY password_hash.txt /crypto/password_hash.txt
COPY flag.txt /crypto/flag.txt

RUN chown -R cryptouser /crypto
RUN chmod -R 777 /crypto

EXPOSE 7393

ENTRYPOINT ["/crypto/start.sh"]
