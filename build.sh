#!/bin/bash
if [ ! -d "bin" ]; then
    mkdir bin
fi

g++ -std=c++20 -c ./src/LockObject.cpp -o ./bin/LockObject.o
g++ -std=c++20 -c ./src/Lock.cpp -o ./bin/Lock.o
g++ -std=c++20 -c ./src/boilerplate.cpp -o ./bin/boilerplate.o
g++ -std=c++20 -c ./src/Database.cpp -o ./bin/Database.o
g++ -std=c++20 -c ./src/Migrations.cpp -o ./bin/Migrations.o
g++ -std=c++20 -c ./src/Schemas.cpp -o ./bin/Schemas.o
g++ -std=c++20 -c ./src/Fss_File.cpp -o ./bin/Fss_File.o
g++ -std=c++20 -c ./src/Indexing.cpp -o ./bin/Indexing.o
g++ -std=c++20 -c ./src/RuntimeState.cpp -o ./bin/RuntimeState.o
g++ -std=c++20 -c ./src/LocalConfig.cpp -o ./bin/LocalConfig.o

gcc -c ./src/sqlite3.c -o ./bin/sqlite3.o

g++ ./bin/LockObject.o ./bin/Lock.o ./bin/Migrations.o ./bin/Schemas.o ./bin/boilerplate.o ./bin/Database.o ./bin/sqlite3.o ./bin/Fss_File.o ./bin/Indexing.o ./bin/RuntimeState.o ./bin/LocalConfig.o -o ./bin/a.out
