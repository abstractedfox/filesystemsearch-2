#include "Fss_File.hpp"

Fss_File::Fss_File(std::string unresolvedPath, bool isDirectory, VolumeTag_Name volumeTag, std::vector<int> checksum, std::filesystem::file_time_type lastModified, bool fromDb) : unresolvedPath(unresolvedPath), isDirectory(isDirectory), volumeTag(volumeTag), checksum(checksum), lastModified(lastModified), fromDb(fromDb){
    
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
