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
