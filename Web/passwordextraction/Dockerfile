FROM ubuntu:latest

env DEBIAN_FRONTEND="noninteractive"

RUN apt-get update -y && apt-get -y install apache2 mysql-server php libapache2-mod-php php-mysql


COPY start.sh /start.sh
COPY index.html /var/www/html/index.html
COPY login.php /var/www/html/login.php

env APACHE_RUN_USER    www-data
env APACHE_RUN_GROUP   www-data
env APACHE_PID_FILE    /var/run/apache2.pid
env APACHE_RUN_DIR     /var/run/apache2
env APACHE_LOCK_DIR    /var/lock/apache2
env APACHE_LOG_DIR     /var/log/apache2

EXPOSE 80
ENTRYPOINT ["bash","/start.sh"]