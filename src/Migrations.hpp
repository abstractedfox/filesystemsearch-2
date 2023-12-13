#ifndef Migrations_hpp
#define Migrations_hpp

#include <string>
#include "sqlite3.h"
#include "Database.hpp"
#include "DatabaseStructs.hpp"
#include "Constants.hpp"

class Migrations{
public:
    static Result migration1(DbPath dbPath, const Schema* schema);
    static Result localConfig1(DbPath dbPath, const Schema* schema);
};

#endif
