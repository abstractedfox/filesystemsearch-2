//
//  Constants.hpp
//  
//
//  Created by Chris on 11/26/23.
//

#include <string>

#ifndef Constants_h
#define Constants_h

namespace Constants{
    const std::string lockFileName = "fssLock";
    const std::string databaseName = "fssDb.sqlite3";
};

enum Result{
    DEFAULT,
    SUCCESS,
    FAIL,
    CREATE_DATABASE_FAIL,
    LOCK_FAIL,
    GENERIC_SQLITE_FAIL
};

#endif /* Constants_h */
