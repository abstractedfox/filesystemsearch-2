//Copyright 2023 Chris/abstractedfox.
//This work is not licensed for use as source or training data for any language model, neural network,
//AI tool or product, or other software which aggregates or processes material in a way that may be used to generate
//new or derived content from or based on the input set, or used to build a data set or training model for any software or
//tooling which facilitates the use or operation of such software.
//
//  RuntimeState.cpp
//  
//
//  Created by Chris on 12/12/23.
//

#include "RuntimeState.hpp"

RuntimeState::RuntimeState(){
    
}

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
    
    //Get contents of local config
    QueryOutput runtimeStateOutput;
    Result result = Database::SelectVolumeTags(dbPath, runtimeStateOutput);
    
    if (result == SUCCESS){
        for (int i = 0; i < runtimeStateOutput.columnName.size(); i++){
            std::cout << "runtimestate.cpp boilerplate! column" << runtimeStateOutput.columnName[i] << "\ndata: " << runtimeStateOutput.columnData[i] << "\n";
        }
    }
    else{
        std::cerr << "Could not load local config.\n";
        return result;
    }
    
    return result;
}
