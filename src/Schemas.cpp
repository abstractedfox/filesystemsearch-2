//Copyright 2023 Chris/abstractedfox.
//This work is not licensed for use as source or training data for any language model, neural network,
//AI tool or product, or other software which aggregates or processes material in a way that may be used to generate
//new or derived content from or based on the input set, or used to build a data set or training model for any software or
//tooling which facilitates the use or operation of such software.
//
//  Schemas.cpp
//  
//
//  Created by Chris on 11/26/23.
//

#include "Schemas.hpp"

//Each 'schema' is an object describing a database schema. Each one holds a reference to a specific instance of 'Migrations' that implements it, as well as an optional reference to the next 'Schema' that would succeed it. 

const Schema Schemas::schema1 = {
    0, //ID
    //Table vector
    {
        //instances of Table
        {
            "VolumeTags",
            {
                {
                    "Name",
                    "TEXT",
                    "UNIQUE NOT NULL"
                }
            },
        },
        {
            "Files",
            //Column vector
            {
                //instances of Column
                {
                    "Path",
                    "TEXT",
                    "UNIQUE NOT NULL"
                },
                {
                    "IsDirectory",
                    "INTEGER",
                    "NOT NULL"
                },
                {
                    "FkVolumeTag",
                    "TEXT",
                    "NOT NULL"
                },
                {
                    "Checksum",
                    "BLOB",
                    ""
                },
                {
                    "LastModified",
                    "TEXT",
                    ""
                },
                {
                    "FOREIGN KEY(FkVolumeTag) REFERENCES VolumeTags(Name)",
                    "",
                    ""
                },
            },
        },
    },
    &Migrations::migration1, //ptr to init or migration function
    NULL //ptr to next schema
};

const Schema Schemas::localConfig1 = {
    0, //ID
    //Table vector
    {
        //instances of Table
        {
            "VolumeTags",
            //Column vector
            {
                //instances of Column
                {
                    "VolumeTag",
                    "TEXT",
                    ""
                },
                {
                    "RealPath",
                    "TEXT",
                    ""
                }
            },
        }
    },
    &Migrations::localConfig1, //ptr to init or migration function
    NULL //ptr to next schema
};

/*For future sanity, here's a template of an entirely empty schema*/
const Schema Schemas::schemaTemplate = {
    -1, //ID
    //Table vector
    {
        //instances of Table
        {
            "VolumeTags",
            {
                {
                    "Name",
                    "TEXT",
                    "UNIQUE NOT NULL"
                }
            },
        }
    },
    NULL, //ptr to init or migration function
    NULL //ptr to next schema
};

