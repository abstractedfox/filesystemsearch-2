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
