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
    
    for (auto &table : Tables){
        statement.append("CREATE TABLE ");
        statement.append(table.name);
        statement.append(" (");
        
        for (int i = 0; i < table.columns.size(); i++){
            std::string isUnique = "";
            std::string isNotNull = "";
            std::string isPrimaryKey = "";
            if (table.columns[i].UNIQUE){
                isUnique = "UNIQUE ";
            }
            if (table.columns[i].NOT_NULL){
                isNotNull = "NOT NULL ";
            }
            if (table.columnIndexAsPkey > -1){
                isPrimaryKey = "PRIMARY KEY ";
            }
            statement.append(table.columns[i].name);
            statement.append(" ");
            statement.append(table.columns[i].sqlDatatype);
            statement.append(" ");
            
            statement.append(isUnique);
            statement.append(isNotNull);
            statement.append(isPrimaryKey);
            
            if (i != table.columns.size() - 1){
                statement.append(", ");
            }
        }
        statement.append(");\n");
    }
    
    return statement;
}

//Note: because I can't find it in the actual sqlite documentation anywhere,
//the arguments for the sqlite3_exec callback (and thus the callback in RunStatement) are, according to exactly one person on stackoverflow:
//'unused, see documentation') (which??)
//'count' number of columns in the result set
//'data' the row's data
//'columns' the column names

//Accepts a path to the database, opens a connection, and runs the statement
bool Database::RunStatement(std::string path, std::string statement, bool handleOwnLock, int (*callback)(void*, int, char**, char**)){
    LockObject* lock;
    if (handleOwnLock){
        lock = Lock::getLock(path, Constants::lockFileName);
        if (lock == NULL){
            std::cerr << "Failed to get lock";
            return false;
        }
    }
    
    sqlite3* dbHandle;
    int result = sqlite3_open_v2(path.c_str(), &dbHandle, SQLITE_OPEN_READWRITE, NULL);
    
    if (result != SQLITE_OK){
        std::cerr << "Database could not be opened, sqlite error code: " << result << "\n";
    }
    
    result = sqlite3_exec(dbHandle, statement.c_str(), callback, NULL, NULL);
    
    if (result != SQLITE_OK){
        std::cerr << "Could not execute statement. SQLite returned error " << result << ". Here is the statement:\n";
        if (handleOwnLock){
            Lock::releaseLock(lock);
        }
        return false;
    }
    
    if (handleOwnLock){
        Lock::releaseLock(lock);
    }
    return true;
}

//Create a new database file if one doesn't exist
bool Database::Init(std::string path, std::string filename){
    sqlite3* dbHandle;
    std::string fullpath = "";
    fullpath.append(path);
    fullpath.append(filename);    
    
    int dbOpenResult = sqlite3_open_v2(fullpath.c_str(), &dbHandle, SQLITE_OPEN_READWRITE, NULL);
    if (dbOpenResult == SQLITE_CANTOPEN){
        dbOpenResult = sqlite3_open_v2(fullpath.c_str(), &dbHandle, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    }
    
    if (dbOpenResult != SQLITE_OK){
        std::cerr << "Database could not be opened or created, SQLite error code " << dbOpenResult << "\n";
        return false;
    }
    
    return true;
}
