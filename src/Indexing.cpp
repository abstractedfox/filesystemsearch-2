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
std::vector<Fss_File> Indexing::getFilesFromDirectory(std::string path, VolumeTag& volumeTag, std::vector<Fss_File>& directories_out){
    std::vector<Fss_File> files;

    try{
        for(std::filesystem::directory_entry item : std::filesystem::recursive_directory_iterator(path)){
            std::vector<int> empty_checksum;
            std::unique_ptr<Fss_File> file;

            Result result = Indexing::createFss_File(item, volumeTag, empty_checksum, file);

            if (result != SUCCESS){
                std::cerr << __FILE__ << " " << __func__ << " received error code from createFss_File: " << result << "\n";
            }

            if (file.get() != nullptr){
                files.push_back(*file.get());
            }
            else{
                std::cerr << __FILE__ << " " << __func__ << " received nullptr from createFss_File\n";
            }

            if (files.back().get_isDirectory()){
                directories_out.push_back(files.back());
            }
        }
    }
    catch(std::filesystem::filesystem_error e){
        std::cerr << "filesystem::filesystem_error thrown, contents: " << e.what() << "\n";
    }
    catch(std::exception e){
        std::cerr << "Generic exception: " << e.what() << "\n";
    }

    return files;
}

//Create an instance of Fss_File based on a real file. Must pass a valid accompanying VolumeTag instance. Sets 'fromDb' to false implicitly, as anything that gets read off a file system is clearly not data from the database
Result Indexing::createFss_File(std::filesystem::directory_entry file, VolumeTag& volumeTag, std::vector<int> checksum, std::unique_ptr<Fss_File>& out){
    if (!file.exists()){
        return FILE_DOESNT_EXIST;
    }

    //we are searching the full string instead of using filesystem.root_name() because root_name() may not always return the path root as its name + directory separator (ie C: on windows instead of C:\)
    if (file.path().string().find(volumeTag.getRealPath()) != 0){
        std::cerr << "Could not find volume tag real path of [" << volumeTag.getRealPath() << "] in file path [" << file.path().string() << "]\n";
        return VOLUME_TAG_ERROR;
    }

    std::string unresolvedPath = file.path().relative_path();

    out = make_unique<Fss_File>(unresolvedPath, file.is_directory(), volumeTag.getTag(), checksum, file.last_write_time(), false);

    return SUCCESS;
}

//Resolve a real path from an instance of Fss_File and relevant VolumeTag.
//Needs tests written
std::string Indexing::resolvePath(Fss_File* file, VolumeTag* volumeTag, char separatorCharacter){
    if (file->get_volumeTag() == volumeTag->getTag()){
        std::string resolvedPath = volumeTag->getRealPath() + file->get_unresolvedPath();
        
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
