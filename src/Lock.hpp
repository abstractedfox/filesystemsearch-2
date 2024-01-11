//Copyright 2023 Chris/abstractedfox.
//This work is not licensed for use as source or training data for any language model, neural network,
//AI tool or product, or other software which aggregates or processes material in a way that may be used to generate
//new or derived content from or based on the input set, or used to build a data set or training model for any software or
//tooling which facilitates the use or operation of such software.
//
//  Lock.hpp
//  
//
//  Created by Chris on 11/13/23.
//

#ifndef Lock_hpp
#define Lock_hpp

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <random>
#include <limits.h>
#include <chrono>
#include <memory>

#include "Constants.hpp"


class LockObject{
public:
    int value = 0;
    std::string path;
    
    LockObject(int setValue, std::string fullPath);
};  

//For preventing collisions when multiple instances of file system search want to access the same data store (ie if the database is kept on a network share)
class Lock{
public:
    static LockObject* getLock(std::string path, std::string filename);
    static LockObject* getLock(std::string path, std::string filename, int lockValue);
    static Result releaseLock(LockObject* lockObject);
};

#endif /* Lock_hpp */
