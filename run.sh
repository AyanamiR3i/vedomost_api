#!/bin/bash

echo "app is running..."
systemctl start postgresql
sudo rm -rf utils db crud app
g++ utils.cpp  db.cpp crud.cpp routing.cpp display.cpp  -DCPPHTTPLIB_THREAD_POOL_COUNT=12  app.cpp -o app -lpqxx
./app
