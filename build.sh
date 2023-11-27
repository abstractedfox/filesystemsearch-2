#!/bin/bash
if [ ! -d "bin" ]; then
    mkdir bin
fi

g++ -std=c++20 -c ./src/LockObject.cpp -o ./bin/LockObject.o
g++ -std=c++20 -c ./src/Lock.cpp -o ./bin/Lock.o
g++ -std=c++20 -c ./src/boilerplate.cpp -o ./bin/boilerplate.o
g++ -std=c++20 -c ./src/Database.cpp -o ./bin/Database.o
g++ -std=c++20 -c ./src/Schemas.cpp -o ./bin/Schemas.o
gcc -c ./src/sqlite3.c -o ./bin/sqlite3.o

g++ ./bin/LockObject.o ./bin/Lock.o ./bin/Schemas.o ./bin/boilerplate.o ./bin/Database.o ./bin/sqlite3.o  -o ./bin/a.out
