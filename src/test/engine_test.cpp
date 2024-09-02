#include <chrono>
#include <thread>

#include "tests.h"
#include "dlEngine.h"
#include "dc_file.h"

dumiengine::DumiEngine* engine = nullptr;

static void init_eng(){

    if(engine){
        delete engine;
    }
    engine = new dumiengine::DumiEngine();
}

static bool loadProg(std::string path){
    
    auto fpath = dcutil::rootDir()/"scripts/test"/path;
    auto data = dcutil::readFileAsString(fpath);

    return engine->loadDCProgram(data) != 0;
}

static void startEngine(){
    engine->start();
}

static void stopEngine(){
    engine->stop();
}

static void test_cores(){

    assertNotThrows([]{
        init_eng();
        assert(loadProg("program1.dc"));
        startEngine();
    });

    stopEngine();
    //engine->setState(dumiengine::STOP);
}

bool test_engine(){
    test_cores();

    delete engine;

    return true;
}