#include "Migrations.hpp"


int Migrations::migration1(std::string pathToDb, const Schema* schema){
    LockObject* lock;
    lock = Lock::getLock(pathToDb, Constants::lockFileName);
    if (lock == NULL){
        std::cerr << "Failed to get lock\n";
        return -1;
    }

    std::string statement = Database::FormStatement_InitSchema(schema->tables);    

    std::cout << "For chris purposes, here is the statement:" << statement << "\n";
    
    int sqliteResult = Database::Init(pathToDb, Constants::databaseName, false);
    
    if (sqliteResult != SQLITE_OK){
        std::cerr << "Sqlite bad, here is the result: " << sqliteResult << "\n";
        return sqliteResult;
    }
    
    sqliteResult = Database::RunStatement(pathToDb, statement, false, NULL);

    std::cout << "For chris purposes, here is the sqlite result: " << sqliteResult << "\n";
    
    Lock::releaseLock(lock);
    return sqliteResult;
}
