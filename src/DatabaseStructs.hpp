#include <iostream>
#include <vector>
#include "Migrations.hpp"

#ifndef DatabaseStructs_hpp
#define DatabaseStructs_hpp

struct Column{
    bool UNIQUE;
    bool NOT_NULL;
    std::string sqlDatatype;
    std::string name;
    
    //note for posterity: second 'const' applies to 'this'
    bool operator==(const Column& compare) const{
        if (UNIQUE == compare.UNIQUE
            && NOT_NULL == compare.NOT_NULL
            && sqlDatatype == compare.sqlDatatype
            && name == compare.name){
            return true;
        }
        return false;
    }
};

class Table{
public:
    std::string name;
    std::vector<Column> columns;
    int columnIndexAsPkey;
};

class Schema{
public:
    std::vector<Table> tables;
    int (*migrate)(std::string pathToDb); //Returns the SQLite result

    Schema* next;
};

#endif
