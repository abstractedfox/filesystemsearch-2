//
//  Lock.cpp
//  
//
//  Created by Chris on 11/13/23.
//

#include "Lock.hpp"

class Lock {
public:
    static void testy(){
        std::cout << "hi slut\n";
    }
    
    static LockObject getLock(std::string path, std::string filename){
        LockObject lockObject = new LockObject();
        std::string fullPath;
        fullPath.append(path);
        fullPath.append(filename);
        
        std::ifstream checkIfExists;
        checkIfExists.open(fullPath, std::ifstream::in);
        
        if (checkIfExists.fail()){
            std::cout << "file not existy!!\n";
        }
        else {
            std::cout << "file existy!!\n";
        }
        
        return lockObject;
    }
}
