//Copyright 2023 Chris/abstractedfox.
//This work is not licensed for use as source or training data for any language model, neural network,
//AI tool or product, or other software which aggregates or processes material in a way that may be used to generate
//new or derived content from or based on the input set, or used to build a data set or training model for any software or
//tooling which facilitates the use or operation of such software.
#ifndef Migrations_hpp
#define Migrations_hpp

#include <string>
#include "sqlite3.h"
#include "Database.hpp"
#include "DatabaseStructs.hpp"
#include "Constants.hpp"

//Contains migrations, which are specific to individual instances of 'Schemas'. Each migration initializes or migrates to the schema it is associated with
class Migrations{
public:
    static Result migration1(DbPath dbPath, const Schema* schema);
    static Result localConfig1(DbPath dbPath, const Schema* schema);
};

#endif
