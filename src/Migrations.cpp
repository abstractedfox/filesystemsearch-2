//Copyright 2023 Chris/abstractedfox.
//This work is not licensed for use as source or training data for any language model, neural network,
//AI tool or product, or other software which aggregates or processes material in a way that may be used to generate
//new or derived content from or based on the input set, or used to build a data set or training model for any software or
//tooling which facilitates the use or operation of such software.
#include "Migrations.hpp"

//A 'migration' in this context is the function implementing a 'Schema' object. Each migration is specific to a schema and vice versa, with each Schema holding a reference to the migration that implements it.

Result Migrations::migration1(DbPath dbPath, const Schema* schema){
    LockObject* lock;
    lock = Lock::getLock(dbPath.pathToDb, Constants::lockFileName);
    if (lock == NULL){
        std::cerr << "Failed to get lock\n";
        return LOCK_FAIL;
    }
    
    std::string statement = Database::FormStatement_InitSchema(schema->tables);    

    std::cout << "Statement being applied:" << statement << "\n";
    
    if (Database::Init(dbPath, false) != SUCCESS){
        std::cerr << "Could not initialize empty database\n";
        return CREATE_DATABASE_FAIL;
    }
    
    if (!Database::RunStatement(dbPath, statement, false, NULL)){
        std::cerr << "Could not run statement against the database\n";
        return GENERIC_SQLITE_FAIL;
    }
    
    Lock::releaseLock(lock);
    return SUCCESS;
}

//yes this has the exact same code as migration1, but I'm still keeping these separate
Result Migrations::localConfig1(DbPath dbPath, const Schema* schema){
    LockObject* lock;
    lock = Lock::getLock(dbPath.pathToDb, Constants::lockFileName);
    if (lock == NULL){
        std::cerr << "Failed to get lock\n";
        return LOCK_FAIL;
    }
    
    std::string statement = Database::FormStatement_InitSchema(schema->tables);

    std::cout << "Statement being applied:" << statement << "\n";
    
    if (Database::Init(dbPath, false) != SUCCESS){
        std::cerr << "Could not initialize empty database\n";
        return CREATE_DATABASE_FAIL;
    }
    
    if (!Database::RunStatement(dbPath, statement, false, NULL)){
        std::cerr << "Could not run statement against the database\n";
        return GENERIC_SQLITE_FAIL;
    }
    
    Lock::releaseLock(lock);
    return SUCCESS;
}
