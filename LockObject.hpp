//
//  LockObject.hpp
//  
//
//  Created by Chris on 11/13/23.
//

#ifndef LockObject_hpp
#define LockObject_hpp

#include <stdio.h>
#include <string>

class LockObject{
public:
    int value = 0;
    std::string path;
    
    LockObject(int setValue, std::string fullPath);
};

#endif /* LockObject_hpp */
