//
//  boilerplate.cpp
//  
//
//  Created by Chris on 11/13/23.
//

#include <stdio.h>
#include <iostream>
#include <random>
#include "Lock.hpp"
#include "LockObject.hpp"
#include "Database.hpp"
#include "Schemas.hpp"

void testDb(){
    //Schema* schematime = &Schemas::testSchema;
    std::cout << "sizey " << Schemas::schemaTemplate.tables.size() << "\n";
    
    std::string path = "";
    std::string filename = "testdb.sqlite3";
    std::string pathOfDb = path + filename;
    /*
    if(Database::Init(path, filename)){
        std::cout << "Database initialized\n";
    }
    
    Column testColumn1 = {false, false, "varchar", "testColumn1"};
    Column testColumn2 = {true, false, "varchar", "testColumn2"};
    Column testColumn3 = {false, true, "varchar", "testColumn3"};
    Column testColumn4 = {true, true, "varchar", "testColumn4"};
    Column testColumn5 = {false, false, "varchar", "testColumn5pkey"};
    
    Table testTable1;
    testTable1.name = "testTable1";
    testTable1.columns.push_back(testColumn1);
    testTable1.columns.push_back(testColumn2);
    testTable1.columns.push_back(testColumn3);
    testTable1.columns.push_back(testColumn4);
    testTable1.columns.push_back(testColumn5);
    testTable1.columnIndexAsPkey = 4;
    */

    Database::Migrate(pathOfDb, &Schemas::schema1);
    
    //Database::RunStatement(pathOfDb, initStatement, true, NULL);
}

void testLock(){
    std::string path = "/Users/chris/Documents/";
    path = "/home/chris/testfiles/";
    std::string lockfileName = "fssLock";
    
    LockObject* test = Lock::getLock(path, lockfileName);
    
    if (test == 0){
        std::cout << "Failed to get lock\n";
    }
    else{
        std::cout << "Received lockobject\n";
    }

    if (Lock::releaseLock(test)){
        std::cout << "Released lock\n";
    }
    else{
        std::cout << "Failed to release lock\n";
    }

}

int main(){
    std::cout << "Let's boil this plate\n";
    //testLock();
    testDb();
    return 0;
}
