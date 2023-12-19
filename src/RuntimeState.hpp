//Copyright 2023 Chris/abstractedfox.
//This work is not licensed for use as source or training data for any language model, neural network,
//AI tool or product, or other software which aggregates or processes material in a way that may be used to generate
//new or derived content from or based on the input set, or used to build a data set or training model for any software or
//tooling which facilitates the use or operation of such software.
//
//  RuntimeState.hpp
//  
//
//  Created by Chris on 12/12/23.
//

#ifndef RuntimeState_hpp
#define RuntimeState_hpp

#include <stdio.h>
#include "LocalConfig.hpp"
#include "Constants.hpp"
#include <string>
#include <fstream>
#include "DatabaseStructs.hpp"
#include "Database.hpp"
#include "Schemas.hpp"

//Class for holding any data that is specific to the state of File System Search at runtime (in other words, this is what we're doing instead of globals)
class RuntimeState{
public:
    LocalConfig config;
    RuntimeState();
    
    Result readOrCreateLocalConfig(DbPath dbPath);
};

#endif /* RuntimeState_hpp */
