FROM alpine

RUN apk add --update socat

RUN addgroup -S ctf

RUN mkdir /rvrs

COPY about_time /rvrs/about_time
COPY flag.txt /rvrs/flag.txt
COPY entry.sh /rvrs/entry.sh

RUN adduser -SDHG ctf rvrsuser
RUN addgroup -S rvrsflag
RUN adduser -SDHG ctf -G rvrsflag --home=/rvrs rvrsflag

RUN chown rvrsflag:rvrsflag /rvrs/flag.txt
RUN chown rvrsflag:rvrsflag /rvrs/about_time
RUN chown rvrsflag:rvrsflag /rvrs

RUN chmod 4755 /rvrs/about_time
RUN chmod 444 /rvrs/flag.txt
RUN chmod 4755 /rvrs/entry.sh

WORKDIR /rvrs

EXPOSE 4321
ENTRYPOINT ["su", "-s", "/bin/sh", "-c", "/rvrs/entry.sh", "rvrsuser"]
