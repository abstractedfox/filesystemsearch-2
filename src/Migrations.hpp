#ifndef Migrations_hpp
#define Migrations_hpp

#include <string>
#include "sqlite3.h"
#include "Database.hpp"
#include "DatabaseStructs.hpp"
#include "Constants.hpp"

class Migrations{
public:
    static int migration1(DbPath dbPath, const Schema* schema);
};

#endif
