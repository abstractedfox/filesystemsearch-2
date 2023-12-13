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

class RuntimeState{
public:
    LocalConfig config;
    
    Result readOrCreateLocalConfig(DbPath dbPath);
};

#endif /* RuntimeState_hpp */
