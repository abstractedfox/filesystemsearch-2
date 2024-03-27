#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <memory>
#include <system_error>

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
    
    VolumeTag tagA("coolvolume", (std::string)"/");
    VolumeTag tagB("anothercoolvolume", (std::string)"C:\\");
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

void testIndexing(){
    bool verbose = false;

    VolumeTag volumeTagA("testrootpath", (std::string)"/");
    std::unique_ptr<Fss_File> fssFileOut;
    
    //test createFss_File / Fss_File instantiation
    std::error_code error;
    std::filesystem::directory_entry testfile(testDb.fullPathToDb(), error);
    if (error){
        fail(__func__, "Failed to instantiate std::filesystem::directory_entry for test database, with error value " + std::to_string(error.value()));
    }
    std::vector<int> dummyChecksum;
    Result result = Indexing::createFss_File(testfile, volumeTagA, dummyChecksum, fssFileOut);

    passfail(result, __func__, "Indexing::createFss_File");

    //Test generation of Fss_Files from a directory
    std::vector<Fss_File> directories;
    std::vector<Fss_File> files = Indexing::getFilesFromDirectory(testDb.pathToDb, volumeTagA, directories);
    std::cout << "Indexing::getFilesFromDirectory for the path " << testDb.pathToDb << " returned " << std::to_string(files.size()) << " results including " << std::to_string(directories.size()) << " directories\n";
    if (verbose){
        std::cout << "Files discovered:\n";
        for (auto file : files){
            std::cout << file.getAttributesAsString() << "------\n";
        }
    }
}

int main(){
    testpath = std::filesystem::current_path();
    testDb = { testpath, "testdb" };
    testConfig = { testpath, "testconfig" };
    
    testLock();
    testDatabase();
    testLocalConfig();
    testIndexing();

    //remove the test db and config
    std::remove(testDb.fullPathToDb().c_str());
    std::remove(testConfig.fullPathToDb().c_str());

    return 0;
}
