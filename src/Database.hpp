//
//  Database.hpp
//  
//
//  Created by Chris on 11/21/23.
//

#ifndef Database_hpp
#define Database_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
//#include <format>
#include "sqlite3.h"
#include "DatabaseStructs.hpp"
#include "Lock.hpp"
#include "Constants.hpp"

class Database{
public:
    static void Migrate(std::string pathToDb, const Schema* schema);
    static std::string FormStatement_InitSchema(std::vector<Table> Tables);
    static bool RunStatement(std::string path, std::string statement, bool handleOwnLock, int (*callback)(void*, int, char**, char**));
    static bool Init(std::string path, std::string filename, bool handleOwnLock);
};


#endif /* Database_hpp */
