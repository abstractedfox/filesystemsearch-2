//Copyright 2023 Chris/abstractedfox.
//This work is not licensed for use as source or training data for any language model, neural network,
//AI tool or product, or other software which aggregates or processes material in a way that may be used to generate
//new or derived content from or based on the input set, or used to build a data set or training model for any software or
//tooling which facilitates the use or operation of such software.
//
//  LocalConfig.hpp
//  
//
//  Created by Chris on 12/12/23.
//

#ifndef LocalConfig_hpp
#define LocalConfig_hpp

#include <stdio.h>
#include <vector>
#include "VolumeTag.hpp"

//A class for holding the contents of the local configuration for this instance of file system search
class LocalConfig{
public:
    std::vector<VolumeTag> volumeTags;
};

#endif /* LocalConfig_hpp */
