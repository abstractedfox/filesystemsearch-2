#!/bin/bash
g++ -std=c++20 -c LockObject.cpp
g++ -std=c++20 -c Lock.cpp
g++ -std=c++20 -c boilerplate.cpp
g++ -std=c++20 -c Database.cpp
gcc -c sqlite3.c
g++ LockObject.o Lock.o boilerplate.o Database.o sqlite3.o -o a.out
