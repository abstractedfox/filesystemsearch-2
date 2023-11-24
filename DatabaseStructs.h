#include <iostream>
#include <vector>

struct Column{
    bool UNIQUE;
    bool NOT_NULL;
    std::string sqlDatatype;
    std::string name;
};

class Table{
    std::string name;
    std::vector<Column> columns;
    Column pKey;
};
