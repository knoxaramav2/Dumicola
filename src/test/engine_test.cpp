#include <chrono>
#include <thread>

#include "tests.h"
#include "dlEngine.h"

dumiengine::DumiEngine* engine = nullptr;

static void init_eng(unsigned cores){
    if(engine){
        delete engine;
    }
    engine = new dumiengine::DumiEngine(cores);
}

static void test_cores(){

    //assertNotThrows([]{
    //    init_eng(dumiengine::THREAD, 4);
    //    engine->setState(dumiengine::RUN);
    //    for(auto i = 0; i < 50; ++i){
    //        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //        engine->update();
    //    }
    //});

    assertNotThrows([]{
        init_eng(4);
        engine->setState(dumiengine::RUN);
        for(auto i = 0; i < 50; ++i){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            engine->update();
        }
    });

    
    //engine->setState(dumiengine::STOP);
}

bool test_engine(){
    test_cores();

    delete engine;

    return true;
}