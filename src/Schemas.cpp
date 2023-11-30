//
//  Schemas.cpp
//  
//
//  Created by Chris on 11/26/23.
//

#include "Schemas.hpp"

//Usage note: The purpose of these is to have a representation of the schema in software so it can determine whether the database matches a known schema, and migrate it if necessary.
//Each schema should have a pointer to a function matching the 'Migration' typedef that, when run against the database, either initializes that schema or migrates that schema from the previous one

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
