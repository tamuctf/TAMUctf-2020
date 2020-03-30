FROM debian:bullseye-slim as build

RUN apt update
RUN apt -y install build-essential gcc-multilib
COPY gunzipasaservice.c /tmp/gunzipasaservice.c
RUN gcc /tmp/gunzipasaservice.c -o /tmp/gunzipasaservice -fno-stack-protector -no-pie -m32

FROM debian:bullseye-slim 
RUN dpkg --add-architecture i386
RUN apt update
RUN apt install -y socat
RUN apt install -y libc6:i386
COPY --from=build /tmp/gunzipasaservice /pwn/gunzipasaservice
COPY flag.txt /pwn/flag.txt

WORKDIR /pwn

EXPOSE 4709

ENTRYPOINT ["sh", "-c", "exec socat -d -d tcp-l:4709,reuseaddr,fork exec:/pwn/gunzipasaservice,stderr"]
