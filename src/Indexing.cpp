//
//  Indexing.cpp
//  
//
//  Created by Chris on 12/12/23.
//

#include "Indexing.hpp"

//Returns a vector containing the contents of a directory as Fss_File
//Currently incomplete! Should probably finish the 'volumetags' functionality or we're going to have a lot of stuff here that needs to be redone/doesn't really work to our spec anyway
std::vector<Fss_File> Indexing::GetFilesFromDirectory(std::string path){
    std::vector<Fss_File> files;
    try{
        for(std::filesystem::directory_entry item : std::filesystem::recursive_directory_iterator(path)){
            
            Fss_File newfile;
        }
    }
    catch(std::filesystem::filesystem_error e){
        std::cout << "filesystem::filesystem_error thrown, contents: " << e.what() << "\n";
    }
    catch(std::exception e){
        std::cout << "Generic exception: " << e.what() << "\n";
    }
    return files;
}
