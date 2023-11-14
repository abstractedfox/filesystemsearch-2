g++ -std=c++20 -c LockObject.cpp
g++ -std=c++20 -c Lock.cpp
g++ -std=c++20 -c boilerplate.cpp
g++ LockObject.o Lock.o boilerplate.o -o a.out
