//Copyright 2023 Chris/abstractedfox.
//This work is not licensed for use as source or training data for any language model, neural network,
//AI tool or product, or other software which aggregates or processes material in a way that may be used to generate
//new or derived content from or based on the input set, or used to build a data set or training model for any software or
//tooling which facilitates the use or operation of such software.

#ifndef DatabaseStructs_hpp
#define DatabaseStructs_hpp

#include <iostream>
#include <vector>

#include "Constants.hpp"

class Schema; //forward declaration for Migration typedef
class Fss_File; //forward declaration to mitigate circular dependency

//For code clarity (ie making it clear whether a function is returning a 'Result' as defined in Constants.hpp or an SQLite result
typedef int SqliteResult;

//A path to a database; mostly for clarity purposes (ie making it clearer when the path being asked for should be to a database, and making it harder to get mixed up over whether a path is to a directory containing a database or to an actual database file)
struct DbPath{
    std::string pathToDb; //Path to the directory containing the database
    std::string dbFilename; //The filename of the database
    std::string fullPathToDb(){
        if (pathToDb.substr(pathToDb.length() - 1) != Constants::SEPARATOR){
            return pathToDb + Constants::SEPARATOR + dbFilename;
        }
        return pathToDb + dbFilename;
    }
};

typedef Result (*Migration)(DbPath dbPath, const Schema* schema);

typedef int (*SqliteCallback)(void*, int, char**, char**);

//A convenient struct for holding the values returned by sqlite3_exec
struct QueryOutput{
    std::vector<std::string> columnName;
    std::vector<std::string> columnData;
};

//A column in a database
class Column{
public:
    std::string name;
    std::string sqlType;
    std::string constraints;
};

//A table in a database
class Table{
public:
    std::string name;
    std::vector<Column> columns;
};

//Object describing the state of a database. Migration object is a pointer to a function which migrates to or initializes this schema
class Schema{
public:
    int ID;
    std::vector<Table> tables;
    
    Migration migration;
    Schema* next;
};

//Used for holding a string that should resolve to a valid VolumeTag
typedef std::string VolumeTag_Name;

//Class for associating an abstracted volume tag with the path of a specific, real volume on a specific machine
//Should only be used in code associated with resolution of a VolumeTag to a real volume on a specific machine; if passing or retaining the value of a VolumeTag, use VolumeTag_Name
//the RealPath variable should be a literal valid path on a machine, ending in its native separating character (ie a backslash for windows). This is unlike the unresolved paths stored in Fss_File, which should always use /
class VolumeTag{
public:
    std::string tag;
    std::string realPath;
};



#endif
