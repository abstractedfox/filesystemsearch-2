//Copyright 2023 Chris/abstractedfox.
//This work is not licensed for use as source or training data for any language model, neural network,
//AI tool or product, or other software which aggregates or processes material in a way that may be used to generate
//new or derived content from or based on the input set, or used to build a data set or training model for any software or
//tooling which facilitates the use or operation of such software.
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
#include "sqlite3.h"
#include "DatabaseStructs.hpp"
#include "Lock.hpp"
#include "Constants.hpp"

//A class for actions against the database, and abstracting queries from the rest of the codebase
class Database{
public:
    static int Callback(void* outputBufferAsQueryOutput, int count, char** columnData, char** columnName);
    
    static Result SelectVolumeTags(DbPath dbPath, QueryOutput& queryOutput);
    
    static Result Migrate(DbPath dbPath, const Schema* schema);
    
    static std::string FormStatement_InitSchema(std::vector<Table> Tables);
    
    static Result RunStatement(DbPath dbPath, std::string statement, bool handleOwnLock, int (*callback)(void*, int, char**, char**));
    static Result RunStatement(DbPath dbPath, std::string statement, bool handleOwnLock, QueryOutput& queryOutput);
    
    static Result Init(DbPath dbPath, bool handleOwnLock);
};

#endif /* Database_hpp */
