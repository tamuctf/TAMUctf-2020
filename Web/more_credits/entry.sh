#!/bin/bash

cd /auth-system
service postgresql start
psql -U postgres -c 'CREATE DATABASE "auth-system"'
node server.js
