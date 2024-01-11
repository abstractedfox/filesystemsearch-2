//Copyright 2023 Chris/abstractedfox.
//This work is not licensed for use as source or training data for any language model, neural network,
//AI tool or product, or other software which aggregates or processes material in a way that may be used to generate
//new or derived content from or based on the input set, or used to build a data set or training model for any software or
//tooling which facilitates the use or operation of such software.

#include "Database.hpp"

Result Database::AddFiles(DbPath dbPath, std::vector<Fss_File> files, bool handleOwnLock){
    LockObject* lock;
    if (handleOwnLock){
        lock = Lock::getLock(dbPath.pathToDb, Constants::lockFileName);
        if (lock == NULL){
            std::cerr << "Failed to get lock\ns";
            return LOCK_FAIL;
        }
    }

    std::string statement = "INSERT INTO Files(Path, IsDirectory, FkVolumeTag, Checksum, LastModified) VALUES ";
    
    for (int i = 0; i < files.size(); i++){
           
    }

    if (handleOwnLock){
        Result lockReleaseResult = Lock::releaseLock(lock);
        if (lockReleaseResult != SUCCESS){
            return lockReleaseResult;
        }
    }

    return SUCCESS;
}

//Callback for sqlite3_exec
//'outputBufferAsQueryOutput' is an output buffer as a QueryOutput object; it's a void* because this value is passed through sqlite to get here
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

    //note:sqlite stops the query if this returns nonzero
    return 0;
}

Result Database::AddVolumeTag(DbPath localConfigDb, VolumeTag volumeTag){
    std::string statement = "INSERT INTO VolumeTags(VolumeTag, RealPath) VALUES ('";
    statement += volumeTag.tag + "', '" + volumeTag.realPath + "');";
    
    QueryOutput queryOutput;
    Result result = Database::RunStatement(localConfigDb, statement, false, queryOutput);
    
    return result;
}

//Return any VolumeTags in a local config database. Result is returned into the vector passed to 'output'
Result Database::GetVolumeTags(DbPath localConfigDb, std::vector<VolumeTag> &output){
    const std::string statement = "SELECT * FROM VolumeTags";
    QueryOutput queryOutput;
    Result queryResult = Database::RunStatement(localConfigDb, statement, true, queryOutput);
    if (queryResult != SUCCESS){
        return queryResult;
    }
    
    for (int i = 0; i < queryOutput.columnName.size(); i += 2){
        VolumeTag tag;
        if (queryOutput.columnName[i] == "VolumeTag"){
            tag.tag = queryOutput.columnData[i];
        }
        else{
            std::cerr << __FILE__ << " Unexpected column name, expected VolumeTag and got " << queryOutput.columnName[i] << "\n";
            return INCORRECT_DATA_FAIL;
        }
        if (queryOutput.columnName[i + 1] == "RealPath"){
            tag.realPath = queryOutput.columnData[i + 1];
        }
        else{
            std::cerr << __FILE__ << " Unexpected column name, expected RealPath and got " << queryOutput.columnName[i] << "\n";
            return INCORRECT_DATA_FAIL;
        }
        output.push_back(tag);
    }
    return SUCCESS;
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

//Uses Database::Callback to retrieve data using sqlite3_exec, and returns the results to queryOutput
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


//for posterity:
//the arguments for the sqlite3_exec callback (and thus the callback in RunStatement) are, according to exactly one person on stackoverflow:
//'unused' this argument is passed to the callback by sqlite3_exec and contains whatever was passed to sqlite3_exec as its 4th argument (ie so you can actually use the data it's passed)
//'count' number of rows in the result set
//'data' the row's data
//'columns' the column names
