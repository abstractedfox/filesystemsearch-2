//
//  Schemas.cpp
//  
//
//  Created by Chris on 11/26/23.
//

#include "Schemas.hpp"

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
                    "columnName",
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

