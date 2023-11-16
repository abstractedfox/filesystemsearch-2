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
    
    std::fstream writeLockFile;
    writeLockFile.open(fullPath, std::fstream::out);
    if (writeLockFile.fail()){
        std::cerr << "Creation of lock file failed\n";
        return 0;
    }
    
    std::mt19937 randomGenerator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> lockValueRandom(INT_MIN, INT_MAX);
    int lockValue = randomGenerator();
    
    LockObject* lockObject = new LockObject(lockValue, fullPath);
    
    writeLockFile << lockValue;
    
    int size = writeLockFile.tellp();
    std::cout << "size of lockfile: " << size << "\n";
    char* buffer = new char[size];
    writeLockFile.seekg(0);
    writeLockFile.read(buffer, size);
    int checkValue = buffer[0];
    std::cout << lockValue << " " << checkValue << "\n";
    
    return lockObject;
}

bool Lock::releaseLock(LockObject* lockObject){
    std::ifstream readLockFile;
    readLockFile.open(lockObject->path, std::ifstream::in);

    return true;
}
