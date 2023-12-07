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

class Column{
public:
    std::string name;
    std::string sqlType;
    std::string constraints;
};

class Table{
public:
    std::string name;
    //std::vector<Column> columns;
    std::vector<Column> columns;
};

class Schema{
public:
    int ID;
    std::vector<Table> tables;
    
    Migration migration;
    Schema* next;
};


#endif
