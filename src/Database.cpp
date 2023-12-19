//Copyright 2023 Chris/abstractedfox.
//This work is not licensed for use as source or training data for any language model, neural network,
//AI tool or product, or other software which aggregates or processes material in a way that may be used to generate
//new or derived content from or based on the input set, or used to build a data set or training model for any software or
//tooling which facilitates the use or operation of such software.
//
//  Database.cpp
//  
//
//  Created by Chris on 11/21/23.
//

#include "Database.hpp"


//for posterity:
//the arguments for the sqlite3_exec callback (and thus the callback in RunStatement) are, according to exactly one person on stackoverflow:
//'unused' this argument is passed to the callback by sqlite3_exec and contains whatever was passed to sqlite3_exec as its 4th argument (ie so you can actually use the data it's passed)
//'count' number of rows in the result set
//'data' the row's data
//'columns' the column names

int Database::Callback(void* outputBufferAsQueryOutput, int count, char** columnData, char** columnName){
    QueryOutput* output = (QueryOutput*)outputBufferAsQueryOutput;
    for (int i = 0; i < count; i++){
        if (columnName[i] != NULL){
            output->columnName.push_back(columnName[i]);
        }
        else{
            output->columnName.push_back("");
        }
        
        if (columnData[i] != NULL){
            output->columnData.push_back(columnData[i]);
        }
        else{
            output->columnData.push_back("");
        }
    }
    
    return 0;
}

Result Database::SelectVolumeTags(DbPath dbPath, QueryOutput& queryOutput){
    const std::string statement = "SELECT * FROM VolumeTags";
    return Database::RunStatement(dbPath, statement, true, queryOutput);
}

Result Database::Migrate(DbPath dbPath, const Schema* schema){
    return schema->migration(dbPath, schema);
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
            statement.append(table.columns[i].name);
            statement.append(" ");
            statement.append(table.columns[i].sqlType);
            statement.append(" ");
            
            statement.append(table.columns[i].constraints);
            
            if (i != table.columns.size() - 1){
                statement.append(", ");
            }
        }
        statement.append(");\n");
    }
    
    return statement;
}

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

Result Database::RunStatement(DbPath dbPath, std::string statement, bool handleOwnLock, QueryOutput& queryOutput){
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
    
    result = sqlite3_exec(dbHandle, statement.c_str(), &Database::Callback, &queryOutput, NULL);
    
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
Result Database::Init(DbPath dbPath, bool handleOwnLock){
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
