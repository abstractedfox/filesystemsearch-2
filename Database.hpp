//
//  Database.hpp
//  
//
//  Created by Chris on 11/21/23.
//

#ifndef Database_hpp
#define Database_hpp

#include <stdio.h>
#include "sqlite3.h"
#include <iostream>
#include "DatabaseStructs.h"

#endif /* Database_hpp */
class Database{
public:
    static bool Init(std::string path, std::string filename);
};
