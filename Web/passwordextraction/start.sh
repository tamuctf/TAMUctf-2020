chown -R mysql:mysql /var/lib/mysql /var/run/mysqld

service mysql start

mysql -u root -e "CREATE DATABASE db; GRANT ALL PRIVILEGES ON *.* TO 'webserver'@'localhost' IDENTIFIED BY 'wBUs?kWKvXDV?V%xQwj^=xqZGL*29wGP';"
mysql -u root -e "USE db; CREATE TABLE accounts (username varchar(32), password varchar(32) collate utf8_bin);"
mysql -u root -e "USE db; INSERT INTO accounts (username,password) VALUES ('admin', 'gigem{h0peYouScr1ptedTh1s}');"

apache2 -D FOREGROUND
