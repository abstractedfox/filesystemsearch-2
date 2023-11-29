//
//  Schemas.cpp
//  
//
//  Created by Chris on 11/26/23.
//

#include "Schemas.hpp"

const Schema Schemas::schema1 = {
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
            -1 //pkey as an index in the columns vector
        }
    },
    &Migrations::migration1,
    NULL //ptr to next schema
};


/*For future sanity, here's a template of an entirely empty schema*/
const Schema Schemas::schemaTemplate = {
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
            -1 //pkey as an index in the columns vector
        }
    },
    NULL, //ptr to init or migration function
    NULL //ptr to next schema
};
