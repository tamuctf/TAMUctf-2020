FROM ubuntu:latest

RUN mkdir -p /data/db
RUN apt update && apt install -y npm wget vim
RUN wget -O - https://deb.nodesource.com/setup_13.x | bash
RUN apt install -y nodejs
RUN echo "deb http://apt.postgresql.org/pub/repos/apt/ bionic-pgdg main" | tee /etc/apt/sources.list.d/pgdg.list
RUN wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | apt-key add - 
RUN apt update
RUN export DEBIAN_FRONTEND=noninteractive && apt install -y postgresql-11
RUN ln -fs /usr/share/zoneinfo/America/Chicago /etc/localtime
RUN dpkg-reconfigure --frontend noninteractive tzdata

RUN mkdir auth-system && cd auth-system && mkdir models inventory views
RUN npm init -f
RUN npm install --save bcrypt body-parser cookie-parser express express-session express-rate-limit morgan pg sequelize pug
RUN mv /node_modules /auth-system
RUN mv /package.json /auth-system
COPY models /auth-system/models/
COPY inventory /auth-system/inventory/
COPY views /auth-system/views/
COPY entry.sh /auth-system/
COPY server.js /auth-system/
COPY pg_hba.conf /etc/postgresql/11/main/pg_hba.conf

EXPOSE 80

ENTRYPOINT ["/auth-system/entry.sh"]
