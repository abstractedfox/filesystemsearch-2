#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

#include "RuntimeState.hpp"

std::string testpath = "";
DbPath testDb { testpath, "testdb" };
DbPath testConfig { testpath, "testconfig" };

void pass(){
    std::cout << "Pass: ";
}

void pass(std::string function, std::string info){
    std::cout << "Pass: " << function << " " << info << "\n";
}
void fail(){
    std::cout << "Fail: ";
}

void fail(std::string function, std::string info){
    std::cout << "Fail: " << function << " " << info << "\n";
}

void fail(Result result){
    std::cout << "Fail (" << result << "): \n";
}

void passfail(Result result, std::string function, std::string info){
    if (result == SUCCESS){
        std::cout << "Pass: " << function << " " << info << "\n";
    }
    else{
        std::cout << "Fail (" << result << "): " << function << " " << info << "\n";
    }
}

void testLock(){
    const std::string lockfileName = "fssLockTest";
    
    LockObject* test = Lock::getLock(testpath, lockfileName);
    
    if (test == NULL){
        fail();
        std::cout << __func__ << " acquire lock\n";
    }
    else{
        pass();
        std::cout << __func__ << " acquire lock\n";
    }
    Result result = Lock::releaseLock(test);
    if (result == SUCCESS){
        pass();
        std::cout << __func__ << " release lock\n";
    }
    else{
        fail();
        std::cout << __func__ << " release lock\n";
    }
}

void testDatabase(){
    //if a test database is left over from a previous test or a crash, delete it
    std::ifstream checkIfExists;
    checkIfExists.open(testDb.fullPathToDb(), std::ifstream::in);
    if (!checkIfExists.fail()){
        std::remove(testDb.fullPathToDb().c_str());
    }    

    Result result = Database::Init(testDb, true);
    passfail(result, __func__, "Database::Init");
    
    std::string statement = "select * from sqlite_master;";
    QueryOutput output;
    result = Database::RunStatement(testDb, statement, true, output);
    passfail(result, __func__, "Database::RunStatement with this statement: " + statement);
    
    result = Migrations::migration1(testDb, &Schemas::schema1);
    passfail(result, __func__, "Perform Migrations::migration1 against the test database");
}

void testLocalConfig(){
    RuntimeState state;
    Result result = state.readOrCreateLocalConfig(testConfig);
    passfail(result, __func__, "RuntimeState.readOrCreateLocalConfig");
    
    VolumeTag tagA = {"coolvolume", "/"};
    VolumeTag tagB = {"anothercoolvolume", "C:\""};
    Database::AddVolumeTag(testConfig, tagA);
    result = Database::AddVolumeTag(testConfig, tagB);
    passfail(result, __func__, "Database::AddVolumeTag");

    std::vector<VolumeTag> volumetags;
    result = Database::GetVolumeTags(testConfig, volumetags);    
    passfail(result, __func__, "Database::GetVolumeTags");
    if (volumetags.size() != 2){
        fail(__func__, "GetVolumeTags returned incorrect number of results, expected 2 and received " + std::to_string(volumetags.size())); 
    }

}

int main(){
    testLock();
    testDatabase();
    testLocalConfig();

    //remove the test db and config
    std::remove(testDb.fullPathToDb().c_str());
    std::remove(testConfig.fullPathToDb().c_str());

    return 0;
}
