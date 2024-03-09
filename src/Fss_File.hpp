//Copyright 2023 Chris/abstractedfox.
//This work is not licensed for use as source or training data for any language model, neural network,
//AI tool or product, or other software which aggregates or processes material in a way that may be used to generate
//new or derived content from or based on the input set, or used to build a data set or training model for any software or
//tooling which facilitates the use or operation of such software.
#ifndef Fss_File_hpp
#define Fss_File_hpp

#include <string>
#include <vector>
#include <filesystem>
#include <chrono>
#include <format>

#include "DatabaseStructs.hpp"

//'File System Search file'. A class for containing info about a file.
//An instance of Fss_File is immutable once constructed; this is to discourage usage that could result in discrepancies or confusion (ie modifying one and assuming it would modify the data in the database)

//Unlike the path root referred to by a VolumeTag, the 'unresolvedPath' of a Fss_File is not specific to a single machine. This value should always use a forward slash as the separating character, and should not begin with a slash, semantically reflecting that they are relative paths without roots
class Fss_File{
public:
    /*Fss_File(std::string fullPath, bool isDirectory, VolumeTag_Name VolumeTag, std::vector<int> checksum, std::filesystem::file_time_type lastModified, bool fromDb);*/
    
    Fss_File();

    Fss_File(std::string set_unresolvedPath, bool set_isDirectory, VolumeTag_Name set_VolumeTag, std::vector<int> set_checksum, std::filesystem::file_time_type set_lastModified, bool set_fromDb);
    
    bool get_isDirectory() const;
    std::string get_unresolvedPath() const;
    VolumeTag_Name get_volumeTag() const;
    std::vector<int> get_checksum() const;
    std::filesystem::file_time_type get_lastModified() const;
    bool isFromDb() const;

    //for debugging purposes
    std::string getAttributesAsString();

private:
    bool isDirectory;
    std::string unresolvedPath;
    VolumeTag_Name volumeTag;
    std::vector<int> checksum;
    std::filesystem::file_time_type lastModified;

    bool fromDb; //Should be used to indicate whether this Fss_File was created from data in the database
};

#endif
