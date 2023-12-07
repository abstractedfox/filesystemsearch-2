//
//  Database.cpp
//  
//
//  Created by Chris on 11/21/23.
//

#include "Database.hpp"

void Database::Migrate(DbPath dbPath, const Schema* schema){
    schema->migration(dbPath, schema);
}

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
            if (table.columnIndexAsPkey  == i){
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
Result Database::RunStatement(DbPath dbPath, std::string statement, bool handleOwnLock, int (*callback)(void*, int, char**, char**)){
    LockObject* lock;
    if (handleOwnLock){
        lock = Lock::getLock(dbPath.pathToDb, Constants::lockFileName);
        if (lock == NULL){
            std::cerr << "Failed to get lock\ns";
            return LOCK_FAIL;
        }
    }
    
    sqlite3* dbHandle;
    int result = sqlite3_open_v2(dbPath.fullPathToDb().c_str(), &dbHandle, SQLITE_OPEN_READWRITE, NULL);
    
    if (result != SQLITE_OK){
        std::cerr << "Database could not be opened, sqlite error code: " << result << "\n";
    }
    
    result = sqlite3_exec(dbHandle, statement.c_str(), callback, NULL, NULL);
    
    if (result != SQLITE_OK){
        std::cerr << "Could not execute statement. SQLite returned error " << result << ". Here is the statement:\n" << statement << "\n";
        if (handleOwnLock){
            Lock::releaseLock(lock);
        }
        return GENERIC_SQLITE_FAIL;
    }
    
    if (handleOwnLock){
        if (Lock::releaseLock(lock) != SUCCESS){
            return LOCK_FAIL;
        }
    }
    return SUCCESS;
}

//Create a new database file if one doesn't exist
Result Database::Init(DbPath dbPath, std::string filename, bool handleOwnLock){
    LockObject* lock;
    if (handleOwnLock){
        lock = Lock::getLock(dbPath.pathToDb, Constants::lockFileName);
        if (lock == NULL){
            std::cerr << "Failed to get lock\n";
            return LOCK_FAIL;
        }
    }
    
    sqlite3* dbHandle;
    
    SqliteResult dbOpenResult = sqlite3_open_v2(dbPath.fullPathToDb().c_str(), &dbHandle, SQLITE_OPEN_READWRITE, NULL);
    if (dbOpenResult == SQLITE_CANTOPEN){
        dbOpenResult = sqlite3_open_v2(dbPath.fullPathToDb().c_str(), &dbHandle, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    }
    
    if (dbOpenResult != SQLITE_OK){
        std::cerr << "Database could not be opened or created, SQLite error code " << dbOpenResult << "\n";
        
        if (handleOwnLock){
            Result lockReleaseResult = Lock::releaseLock(lock);
            if (lockReleaseResult != SUCCESS){
                return lockReleaseResult;
            }
        }
        return CREATE_DATABASE_FAIL;
    }
    if (handleOwnLock){
        Result lockReleaseResult = Lock::releaseLock(lock);
        if (lockReleaseResult != SUCCESS){
            return lockReleaseResult;
        }
    }
    return SUCCESS;
}
