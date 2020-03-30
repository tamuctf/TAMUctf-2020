FROM openjdk:7-jdk-alpine as build
# we need a different version of the jdk because the ssl is broken in the vulnerable version

COPY too-many-credits/ /opt/too-many-credits

RUN cd /opt/too-many-credits; ./gradlew distTar

FROM openjdk:7u91-jre-alpine

RUN apk add --no-cache --update python3 bash

EXPOSE 8080

COPY --from=build /opt/too-many-credits/build/distributions/credits-1.0.0-SNAPSHOT.tar /opt/credits-1.0.0-SNAPSHOT.tar
RUN cd /opt; tar xf credits-1.0.0-SNAPSHOT.tar; rm credits-1.0.0-SNAPSHOT.tar

COPY flag2.txt /opt/credits-1.0.0-SNAPSHOT/flag.txt

WORKDIR /opt/credits-1.0.0-SNAPSHOT

RUN adduser -SDH credits

CMD ["su", "-s", "/bin/sh", "-c", "/opt/credits-1.0.0-SNAPSHOT/bin/credits --server.port=8080", "credits"]
