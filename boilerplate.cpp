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

void testLock(){
    std::string path = "/Users/chris/Documents/";
    LockObject* test = Lock::getLock(path, "fssLock");
    
    if (test == 0){
        std::cout << "Failed to get lock\n";
    }
    else{
        std::cout << "Received lockobject\n";
    }
}

int main(){
    std::cout << "Let's boil this plate\n";
    testLock();
    
    return 0;
}
