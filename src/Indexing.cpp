//Copyright 2023 Chris/abstractedfox.
//This work is not licensed for use as source or training data for any language model, neural network,
//AI tool or product, or other software which aggregates or processes material in a way that may be used to generate
//new or derived content from or based on the input set, or used to build a data set or training model for any software or
//tooling which facilitates the use or operation of such software.
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
            //Fss_File newfile;
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

//Create an instance of Fss_File representing a real file
//Must be passed a valid volume tag for the volume the file is on
Result Indexing::createFss_File(std::string pathToFile, VolumeTag& volumeTag, std::unique_ptr<Fss_File>& out){
    
    if (pathToFile.find(volumeTag.realPath) != 0){
        std::cerr << "Could not find volume tag real path of [" << volumeTag.realPath << "] in file path [" << pathToFile << "]\n";
        return VOLUME_TAG_ERROR;
    }
    
    std::string unresolvedPath = pathToFile.substr(volumeTag.realPath.length());
    
    std::cout << __FILE__ << ": unresolvedPath: " << unresolvedPath << "\n";
    
    return DEFAULT;
}

//Resolve a real path from an instance of Fss_File and relevant VolumeTag.
//Needs tests written
std::string Indexing::resolvePath(Fss_File* file, VolumeTag* volumeTag, char separatorCharacter){
    if (file->get_volumeTag() == volumeTag->tag){
        std::string resolvedPath = volumeTag->realPath + file->get_unresolvedPath();
        
        if (separatorCharacter != '/'){
            int separatorPos = resolvedPath.find('/');
            while (separatorPos != std::string::npos){
                resolvedPath.replace(separatorPos, 1, &separatorCharacter);
                separatorPos = resolvedPath.find('/');
            }
        }
    }
    
    return "";
}
