//Copyright 2023 Chris/abstractedfox.
//This work is not licensed for use as source or training data for any language model, neural network,
//AI tool or product, or other software which aggregates or processes material in a way that may be used to generate
//new or derived content from or based on the input set, or used to build a data set or training model for any software or
//tooling which facilitates the use or operation of such software.

#include <iostream>
#include <vector>
#include "Migrations.hpp"
#include "Constants.hpp"

#ifndef DatabaseStructs_hpp
#define DatabaseStructs_hpp

class Schema; //forward declaration for Migration typedef

typedef int SqliteResult;

struct DbPath{
    std::string pathToDb; //Path to the directory containing the database
    std::string dbFilename; //The filename of the database
    std::string fullPathToDb(){
        return pathToDb + dbFilename;
    }
};

typedef Result (*Migration)(DbPath dbPath, const Schema* schema);

typedef int (*SqliteCallback)(void*, int, char**, char**);

struct QueryOutput{
    std::vector<std::string> columnName;
    std::vector<std::string> columnData;
};

class Column{
public:
    std::string name;
    std::string sqlType;
    std::string constraints;
};

class Table{
public:
    std::string name;
    std::vector<Column> columns;
};

//Object describing the state of a database. Migration object is a pointer to a function which migrates to or initializes this schema
class Schema{
public:
    int ID;
    std::vector<Table> tables;
    
    Migration migration;
    Schema* next;
};


#endif
