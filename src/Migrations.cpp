#include "Migrations.hpp"


Result Migrations::migration1(DbPath dbPath, const Schema* schema){
    LockObject* lock;
    lock = Lock::getLock(dbPath.pathToDb, Constants::lockFileName);
    if (lock == NULL){
        std::cerr << "Failed to get lock\n";
        return LOCK_FAIL;
    }

    std::string statement = Database::FormStatement_InitSchema(schema->tables);    

    std::cout << "For chris purposes, here is the statement:" << statement << "\n";
    
    if (Database::Init(dbPath, Constants::databaseName, false) != SUCCESS){
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
