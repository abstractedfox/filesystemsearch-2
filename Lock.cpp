//
//  Lock.cpp
//  
//
//  Created by Chris on 11/13/23.
//

#include "Lock.hpp"
#include "LockObject.hpp"

void Lock::testy(){
    std::cout << "hi\n";
}

LockObject* Lock::getLock(std::string path, std::string filename){
    std::string fullPath;
    fullPath.append(path);
    fullPath.append(filename);
    
    std::ifstream checkIfExists;
    checkIfExists.open(fullPath, std::ifstream::in);
    
    if (!checkIfExists.fail()){
        //There is already a lock file
        std::cerr << "Lock file already exists; does someone else already have a lock?\n";
        return 0;
    }
    
    std::ofstream writeLockFile;
    writeLockFile.open(fullPath, std::ofstream::out);
    if (writeLockFile.fail()){
        std::cerr << "Creation of lock file failed\n";
        return 0;
    }
    
    std::default_random_engine randomGenerator;
    std::uniform_int_distribution<int> lockValueRandom(INT_MIN, INT_MAX);
    int lockValue = lockValueRandom(randomGenerator);
    
    LockObject* lockObject = new LockObject(lockValue);
    
    writeLockFile << lockValue;
    
    return lockObject;
}
