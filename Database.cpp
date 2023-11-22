//
//  Database.cpp
//  
//
//  Created by Chris on 11/21/23.
//

#include "Database.hpp"

void Database::SQLiteBoilerplate(){
    sqlite3* handle;
    
    int result = sqlite3_open_v2("asdf", &handle, SQLITE_OPEN_READWRITE, NULL);
    
    std::cout << "jawn: " << result << "\n";
}
