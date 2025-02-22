#!/bin/bash

echo "app is running..."
systemctl start postgresql
sudo rm -rf utils init app
g++ utils.cpp init.cpp db.cpp  app.cpp -o app -lpqxx
./app
