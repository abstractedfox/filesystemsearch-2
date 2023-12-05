//
//  Lock.hpp
//  
//
//  Created by Chris on 11/13/23.
//

#ifndef Lock_hpp
#define Lock_hpp

#include <stdio.h>
#include "LockObject.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <random>
#include "limits.h"
#include <chrono>
#include "Constants.hpp"

class Lock{
public:
    static LockObject* getLock(std::string path, std::string filename);
    static LockObject* getLock(std::string path, std::string filename, int lockValue);
    static Result releaseLock(LockObject* lockObject);
};

#endif /* Lock_hpp */
