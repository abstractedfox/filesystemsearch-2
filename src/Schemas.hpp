//
//  Schemas.hpp
//  
//
//  Created by Chris on 11/26/23.
//

#ifndef Schemas_hpp
#define Schemas_hpp

#include "DatabaseStructs.hpp"

namespace Schemas{
    /*For future sanity, here's a template of an entirely empty schema*/
    const Schema schemaTemplate = {
        //Table vector
        {
            //instances of Table
            {
                "tableName",
                //Column vector
                {
                    //instances of Column
                    {
                        false, //UNIQUE
                        false, //NOT_NULL
                        "varchar",
                        "columnName"
                    }
                },
                NULL //pkey as a pointer
            }
        },
        NULL, //ptr to init or migration function
        NULL //ptr to next schema
    };
}

#endif /* Schemas_h */
