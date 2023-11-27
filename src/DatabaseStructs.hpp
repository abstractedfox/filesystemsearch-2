#include <iostream>
#include <vector>

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
    Column* pKey;
};

class Schema{
public:
    std::vector<Table> tables;
    bool (*migrate)(std::string pathToDb);
    
    Schema* next;
};

#endif
