#!/bin/bash

echo "app is running..."
systemctl start postgresql
sudo rm -rf utils db init crud app
g++ utils.cpp init.cpp db.cpp crud.cpp app.cpp -o app -lpqxx
./app
