//
//  RuntimeState.cpp
//  
//
//  Created by Chris on 12/12/23.
//

#include "RuntimeState.hpp"

//If a local config exists at the given path, open it and set this RuntimeState's LocalConfig.volumeTags to any volume tags contained. If no config exists, make one.
Result RuntimeState::readOrCreateLocalConfig(DbPath dbPath){
    
    std::ifstream checkIfExists;
    checkIfExists.open(dbPath.fullPathToDb(), std::ifstream::in);
    
    if (checkIfExists.fail()){
        Result result = Database::Migrate(dbPath, &Schemas::localConfig1);
        if (result != SUCCESS){
            return result;
        }
    }
    
    
    
    return DEFAULT;
}
