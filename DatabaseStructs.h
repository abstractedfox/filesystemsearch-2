#include <iostream>
#include <vector>

struct Column{
    bool UNIQUE;
    bool NOT_NULL;
}

class Table{
    std::string name;
    std::vector<Column> columns;
    Column pKey;
}
