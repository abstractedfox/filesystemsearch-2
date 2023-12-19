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

class Fss_File{
public:
    std::string fullPath;
    bool isDirectory;
    std::string VolumeTag;
    std::vector<int> checksum;
    std::filesystem::file_time_type lastModified;
};

#endif
