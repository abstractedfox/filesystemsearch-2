//Copyright 2023 Chris/abstractedfox.
//This work is not licensed for use as source or training data for any language model, neural network,
//AI tool or product, or other software which aggregates or processes material in a way that may be used to generate
//new or derived content from or based on the input set, or used to build a data set or training model for any software or
//tooling which facilitates the use or operation of such software.
//
//  boilerplate.cpp
//  
//
//  Created by Chris on 11/13/23.
//


#include <stdio.h>
#include <iostream>
#include <random>
#include <filesystem>

#include "Indexing.hpp"
#include "RuntimeState.hpp"

/*
int callbackTest(void* idk, int columns, char** columnContents, char** columnNames){
    std::cout << "callback start!\n";
    std::cout << "columns in result: " << columns << "\n";
    for (int i = 0; i < columns; i++){
        if (columnNames[i] != NULL){
            std::cout << columnNames[i] << ": ";
        }
        else{
            std::cout << "nullColumnName: ";
        }
        if (columnContents[i] != NULL){
            std::cout << columnContents[i] << "\n";
        }
        else{
            std::cout << "nullContents\n";
        }
    }
    std::cout << "callback end!\n";
    return 0;
}*/

void workingWithFiles(){
    std::filesystem::path thisPath = { "." };
    
    std::vector test = Indexing::GetFilesFromDirectory(".");
}

void testDb(){
    DbPath dbPath = {"", "testdb.sqlite3"};
    
    //If there's still a test db from previous runs, delete it
    std::remove(dbPath.fullPathToDb().c_str());

    std::cout << "Migration result: " << Database::Migrate(dbPath, &Schemas::schema1) << "\n";
    
    std::string testStatement = "select * from sqlite_master";
    
    /*
    std::cout << "Run test statement result code: " << Database::RunStatement(dbPath, testStatement, true, &callbackTest);*/
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
    RuntimeState state;
    DbPath dbPath = {"", "testdb.sqlite3"};
    DbPath conf = {"", "testLocalConf.sqlite3"};
    
    state.readOrCreateLocalConfig(conf);
    
    //testLock();
    //testDb();
    //workingWithFiles();
    return 0;
}
