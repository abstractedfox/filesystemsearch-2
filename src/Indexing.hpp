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
#include "Fss_File.hpp"
#include <string>
#include <iostream>
#include <exception>

class Indexing{
public:
    static std::vector<Fss_File> GetFilesFromDirectory(std::string path);
};

#endif /* Indexing_hpp */
