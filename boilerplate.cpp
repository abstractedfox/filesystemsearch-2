//
//  boilerplate.cpp
//  
//
//  Created by Chris on 11/13/23.
//

#include <stdio.h>
#include <iostream>
#include "Lock.hpp"
#include "LockObject.hpp"
#include "Database.hpp"
#include <random>

void testDb(){
    Database::SQLiteBoilerplate();
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
