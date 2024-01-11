#include "Fss_File.hpp"

Fss_File::Fss_File(std::string fullPath, bool isDirectory, std::string VolumeTag, std::vector<int> checksum, std::filesystem::file_time_type lastModified, bool fromDb) : fullPath(fullPath), isDirectory(isDirectory), VolumeTag(VolumeTag), checksum(checksum), lastModified(lastModified), fromDb(fromDb){

}
