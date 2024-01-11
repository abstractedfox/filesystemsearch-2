//Copyright 2023 Chris/abstractedfox.
//This work is not licensed for use as source or training data for any language model, neural network,
//AI tool or product, or other software which aggregates or processes material in a way that may be used to generate
//new or derived content from or based on the input set, or used to build a data set or training model for any software or
//tooling which facilitates the use or operation of such software.
//
//  Lock.cpp
//  
//
//  Created by Chris on 11/13/23.
//

#include "Lock.hpp"

LockObject::LockObject(int setValue, std::string fullPath){
    value = setValue;
    path = fullPath;
}

//If successful, receive a LockObject. Generates its own random value for the lock.
LockObject* Lock::getLock(std::string path, std::string filename){
    std::mt19937 randomGenerator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> lockValueRandom(INT_MIN, INT_MAX);
    int lockValue = randomGenerator();

    return Lock::getLock(path, filename, lockValue);
}

//If successful, receive a LockObject. Receives a value for the lock as an argument.
LockObject* Lock::getLock(std::string path, std::string filename, int lockValue){
    std::string fullPath;
    fullPath.append(path);
    fullPath.append(filename);
    
    std::ifstream checkIfExists;
    checkIfExists.open(fullPath, std::ifstream::in);
    
    if (!checkIfExists.fail()){
        std::cerr << __FILE__ << " Lock file already exists; does someone else already have a lock?\n";
        return NULL;
    }
    
    std::fstream writeLockFile;
    writeLockFile.open(fullPath, std::fstream::out);
    if (writeLockFile.fail()){
        std::cerr << __FILE__ << " Creation of lock file failed\n";
        return NULL;
    }

    LockObject* lockObject = new LockObject(lockValue, fullPath);

    writeLockFile << lockValue;
    writeLockFile << '\0';
    
    int size = writeLockFile.tellp();

    writeLockFile.close();    

    std::unique_ptr buffer = std::make_unique<char[]>(size);

    std::ifstream readLockFile;
    readLockFile.open(fullPath, std::istream::in);
    
    if (readLockFile.fail()){
        std::cerr << "Failed to open lock file\n";
        readLockFile.close();
        return NULL;
    }

    readLockFile.seekg(0);
    if (!readLockFile.read(buffer.get(), size)){
        std::cerr << "Failed to read lock file\n";
        readLockFile.close();
        return NULL;
    }

    int deserialized = std::stoi(buffer.get());  

    
    if (lockValue != deserialized){
        std::cerr << "Lock file does not match expected lock value\n";
        readLockFile.close();
        return NULL;
    }
    
    readLockFile.close();
    return lockObject;
}

Result Lock::releaseLock(LockObject* lockObject){
    if (lockObject == NULL){
        std::cerr << "LockObject is null, could not release invalid lock\n";
        return LOCK_FAIL;
    }

    std::ifstream readLockFile;
    readLockFile.open(lockObject->path, std::ifstream::in);
    
    int length = std::to_string(lockObject->value).length();
    //char* buffer = new char[length];
    std::unique_ptr buffer = std::make_unique<char[]>(length);    

    try{
        readLockFile.read(buffer.get(), length);
    }
    catch(std::exception& e){
        std::cerr << "Exception thrown reading lock file into buffer; is the file too small?\n" << e.what() << "\n";
        readLockFile.close();
        return FAIL;
    }
    
    int deserialized = std::stoi(buffer.get());
    
    if (deserialized == lockObject->value){
        if (std::remove(lockObject->path.c_str()) != 0){
            std::cerr << "Failed to delete lock file\n";
            readLockFile.close();
            return LOCK_FAIL;
        }
        
        readLockFile.close();
        //delete lockObject;
        return SUCCESS;
    }
    else{
        std::cerr << "Value in lockfile did not match expected value\n";
        readLockFile.close();
        return LOCK_FAIL;
    }

    readLockFile.close();
    return LOCK_FAIL;
}
