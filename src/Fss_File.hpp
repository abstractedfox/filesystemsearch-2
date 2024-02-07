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

//'File System Search file'. A class for containing info about a file.
//An instance of Fss_File is immutable once constructed; this is to discourage usage that could result in discrepancies or confusion (ie modifying one and assuming it would modify the data in the database)
class Fss_File{
public:
    Fss_File(std::string fullPath, bool isDirectory, std::string VolumeTag, std::vector<int> checksum, std::filesystem::file_time_type lastModified, bool fromDb);
    
    bool get_isDirectory() const;
    std::string get_fullPath() const;
    std::string get_VolumeTag() const;
    std::vector<int> get_checksum() const;
    std::filesystem::file_time_type get_lastModified() const;

private:
    bool isDirectory;
    std::string fullPath;
    std::string VolumeTag;
    std::vector<int> checksum;
    std::filesystem::file_time_type lastModified;

    bool fromDb; //Should be used to indicate whether this Fss_File was created from data in the database
};

#endif
