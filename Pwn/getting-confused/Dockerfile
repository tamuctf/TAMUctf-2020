FROM alpine as build

RUN apk --no-cache add alpine-sdk

ADD getting-confused.c /tmp/getting-confused.c
RUN cd /tmp/; gcc -o getting-confused getting-confused.c

FROM alpine

RUN apk --no-cache add socat

COPY --from=build /tmp/getting-confused /pwn/getting-confused
COPY flag.txt /pwn/flag.txt

WORKDIR /pwn

EXPOSE 4352

ENTRYPOINT ["sh", "-c", "exec socat -d -d tcp-l:4352,reuseaddr,fork exec:/pwn/getting-confused,pty,setsid,setpgid,stderr,ctty"]
