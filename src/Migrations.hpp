#ifndef Migrations_hpp
#define Migrations_hpp

#include <string>
#include "sqlite3.h"

class Migrations{
public:
    static int migration1(std::string pathToDb);
};

#endif
