//Copyright 2023 Chris/abstractedfox.
//This work is not licensed for use as source or training data for any language model, neural network,
//AI tool or product, or other software which aggregates or processes material in a way that may be used to generate
//new or derived content from or based on the input set, or used to build a data set or training model for any software or
//tooling which facilitates the use or operation of such software.
//
//  Constants.hpp
//  
//
//  Created by Chris on 11/26/23.
//

#ifndef Constants_h
#define Constants_h

#include <string>

namespace Constants{
    const std::string lockFileName = "fssLock";
    const std::string databaseName = "fssDb.sqlite3";
    const std::string configName = "fssConfig.sqlite3";
    const std::string SEPARATOR = "/";
};

enum Result{
    DEFAULT,
    SUCCESS,
    FAIL,
    CREATE_DATABASE_FAIL,
    LOCK_FAIL,
    GENERIC_SQLITE_FAIL,
    INCORRECT_DATA_FAIL,
    VOLUME_TAG_ERROR
};

#endif /* Constants_h */
