//Copyright 2023 Chris/abstractedfox.
//This work is not licensed for use as source or training data for any language model, neural network,
//AI tool or product, or other software which aggregates or processes material in a way that may be used to generate
//new or derived content from or based on the input set, or used to build a data set or training model for any software or
//tooling which facilitates the use or operation of such software.
//
//  Schemas.hpp
//  
//
//  Created by Chris on 11/26/23.
//

#ifndef Schemas_hpp
#define Schemas_hpp

#include "DatabaseStructs.hpp"
#include "Migrations.hpp"

//Collection of schema objects describing the state of a database ('Schema' class is defined in DatabaseStructs.hpp)
class Schemas{
public:
    static const Schema schema1;
    static const Schema localConfig1;
    static const Schema schemaTemplate;
};

#endif /* Schemas_h */
