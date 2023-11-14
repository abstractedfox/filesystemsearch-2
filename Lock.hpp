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
#include <istream>
#include <iostream>

class Lock{
public:
    static void testy();
    static LockObject getLock(std::string path, std::string filename);
};

#endif /* Lock_hpp */
