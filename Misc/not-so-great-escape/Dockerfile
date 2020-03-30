FROM alpine

RUN apk --no-cache add socat

ENV chroot_dir=/pwn/jail
ENV arch=x86_64
ENV mirror=http://mirror.math.princeton.edu/pub/alpinelinux/
ENV version=2.10.4-r3

WORKDIR ${chroot_dir}

RUN wget ${mirror}/latest-stable/main/${arch}/apk-tools-static-${version}.apk
RUN tar -xzf apk-tools-static-*.apk
RUN rm apk-tools-static-*.apk
RUN ./sbin/apk.static -X ${mirror}/latest-stable/main -U --allow-untrusted --root ${chroot_dir} --initdb add alpine-base

ADD not-so-great-escape.sh /pwn/not-so-great-escape
ADD flag.txt /pwn

ENTRYPOINT ["timeout", "900", "sh", "-c", "exec socat -d -d tcp-l:4353,reuseaddr,fork exec:/pwn/not-so-great-escape,pty,setsid,setpgid,stderr,ctty"]
