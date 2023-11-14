//
//  boilerplate.cpp
//  
//
//  Created by Chris on 11/13/23.
//

#include <stdio.h>
#include <iostream>
#include "Lock.hpp"
#include "LockObject.hpp"

int main(){
    std::string path = "/Users/chris/Documents/git-repos/chrissearch";
    
    std::cout << "Let's boil this plate\n";
    
    //LockObject test = Lock::getLock(path, "jawn.asdf");
    Lock::testy();
    
    return 0;
}
