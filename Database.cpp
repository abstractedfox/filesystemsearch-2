//
//  Database.cpp
//  
//
//  Created by Chris on 11/21/23.
//

#include "Database.hpp"

void Database::SQLiteBoilerplate(){
    sqlite3* handle;
    
    int result = sqlite3_open_v2("asdf", &handle, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    
    std::cout << "jawn: " << result << "\n";
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
