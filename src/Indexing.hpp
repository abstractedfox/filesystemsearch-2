//Copyright 2023 Chris/abstractedfox.
//This work is not licensed for use as source or training data for any language model, neural network,
//AI tool or product, or other software which aggregates or processes material in a way that may be used to generate
//new or derived content from or based on the input set, or used to build a data set or training model for any software or
//tooling which facilitates the use or operation of such software.
//
//  Indexing.hpp
//  
//
//  Created by Chris on 12/12/23.
//

#ifndef Indexing_hpp
#define Indexing_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <exception>
#include <memory>
#include <filesystem>
#include <optional>

#include "Fss_File.hpp"
#include "Constants.hpp"

class Indexing{
public:
    //Returns the contents of a directory as Fss_File instances. Any directories discovered will be included in the output, as well as separately copied in directories_out
    static std::vector<Fss_File> getFilesFromDirectory(std::string path, VolumeTag& volumeTag, std::vector<Fss_File>& directories_out);

    //Returns the contents of a directory as Fss_File instances. Returns any additional directories found via directories_out. Pass 'true' to recursive to recursively run for all subdirectories discovered
    static std::vector<Fss_File> getFilesFromDirectory(std::string path, VolumeTag& volumeTag, std::vector<Fss_File>& directories_out, bool recursive);

    //Create a Fss_File from a real file and a volumetag that resolves to the root path of that file
    static Result createFss_File(std::filesystem::directory_entry file, VolumeTag& volumeTag, std::vector<int> checksum, std::unique_ptr<Fss_File>& out);
    
    static std::string resolvePath(Fss_File* file, VolumeTag* volumeTag, char separatorCharacter);
};

#endif /* Indexing_hpp */
