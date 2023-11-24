//
//  Database.cpp
//  
//
//  Created by Chris on 11/21/23.
//

#include "Database.hpp"

//Form a statement that initializes a database schema (only creates the statement, doesn't run it)
std::string Database::FormStatement_InitSchema(std::vector<Table> Tables){
    if (Tables.size() < 1){
        return NULL;
    }
    
    std::string statement = "";
    
    std::string columnTemplate = "{} {} {} {} {}";
    //name, data type, primary key, unique, not null
    
    for (auto &table : Tables){
        statement.append("CREATE TABLE ");
        statement.append(table.name);
        statement.append(" (");
        
        for (int i = 0; i < table.columns.size(); i++){
            std::string newColumn = "";
            std::string isUnique = "";
            std::string isNotNull = "";
            std::string isPrimaryKey = "";
            if (table.columns[i].UNIQUE){
                isUnique = "UNIQUE";
            }
            if (table.columns[i].isNotNull){
                isNotNull = "NOT NULL";
            }
            if (table.pKey != NULL){
                if (table.pKey == table.columns){
                    isPrimaryKey = "PRIMARY KEY";
                }
            }
            newColumn = std::format(columnTemplate, table.columns[i].name, table.columns[i].sqlDatatype, isPrimaryKey, isUnique, isNotNull);
            
            statement.append(newColumn);
            if (i != table.columns.size() - 1){
                statement.append(", ");
            }
        }
        statement.append(";\n");
    }
}

bool Database::Init(std::string path, std::string filename){
    sqlite3* dbHandle;
    std::string fullpath = "";
    fullpath.append(path);
    fullpath.append(filename);    
    
    int dbOpenResult = sqlite3_open_v2(fullpath.c_str(), &dbHandle, SQLITE_OPEN_READWRITE, NULL);
    if (dbOpenResult == SQLITE_CANTOPEN){
        dbOpenResult = sqlite3_open_v2(fullpath.c_str() &dbHandle, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    }
    
    if (dbOpenResult != SQLITE_OK){
        std::cerr << "Database could not be opened or created, SQLite error code " << dbOpenResult << "\n";
        return false;
    }
}
