#include "Fss_File.hpp"

Fss_File::Fss_File(){
    unresolvedPath = "";
    isDirectory = false;
    checksum = std::vector<int>();

    fromDb = false;
}

Fss_File::Fss_File(std::string set_unresolvedPath, bool set_isDirectory, VolumeTag_Name set_VolumeTag, std::vector<int> set_checksum, std::filesystem::file_time_type set_lastModified, bool set_fromDb){
    unresolvedPath = set_unresolvedPath;
    isDirectory = set_isDirectory;
    volumeTag = set_VolumeTag;
    checksum = set_checksum;
    lastModified = set_lastModified;
    fromDb = set_fromDb;
    
    int backslashPos = unresolvedPath.find("\\");
    while (backslashPos != std::string::npos){
        unresolvedPath.replace(backslashPos, 1, "/");
        backslashPos = unresolvedPath.find("\\");
    }
}

bool Fss_File::get_isDirectory() const{
    return isDirectory;
}

//Get the path of this file without a path root (ie needs to be resolved with its VolumeTag to get a real path the host machine can use)
std::string Fss_File::get_unresolvedPath() const{
    return unresolvedPath;
}

VolumeTag_Name Fss_File::get_volumeTag() const{
    return volumeTag;
}

std::vector<int> Fss_File::get_checksum() const{
    return checksum;
}

std::filesystem::file_time_type Fss_File::get_lastModified() const{
    return lastModified;
}

bool Fss_File::isFromDb() const{
    return fromDb;
}

std::string Fss_File::getAttributesAsString(){
    std::string output = "Unresolved path: " + unresolvedPath + "\n" +
    "isDirectory: " + std::to_string(isDirectory) + "\n" +
    "VolumeTag_Name: " + volumeTag + "\n" +
    "Checksum: ";

    for (auto value : checksum){
        output += std::to_string(value) + " ";
    }

    output += "\nlastModified: " + std::format("{}", lastModified) + "\n" +
    "fromDb: " + std::to_string(fromDb) + "\n";

    return output;
}
