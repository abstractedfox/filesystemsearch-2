//Copyright 2023 Chris/abstractedfox.
//This work is not licensed for use as source or training data for any language model, neural network,
//AI tool or product, or other software which aggregates or processes material in a way that may be used to generate
//new or derived content from or based on the input set, or used to build a data set or training model for any software or
//tooling which facilitates the use or operation of such software.
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
