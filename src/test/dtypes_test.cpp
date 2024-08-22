#include "dataman.h"
#include "kassert.h"
#include "stdio.h"
#include "tests.h"

dataman::DataManager __dcDm;
dataman::AppMemHandle _hndl(50, __dcDm);

void test_converters(){

    //auto converter = __dcDm.getConverter();



    printf("MARK");
}

void register_default_types(){

    __dcDm.registerType<dumisdk::DCBoolean>(0);
    __dcDm.registerType<dumisdk::DCInteger>(0);
    __dcDm.registerType<dumisdk::DCDecimal>(0);
    __dcDm.registerType<dumisdk::DCString>(0);
    __dcDm.registerType<dumisdk::DCList>(0);
    __dcDm.registerType<dumisdk::DCMap>(0);
}

void test_default_assignment(){
    auto intId = __dcDm.newVar<dumisdk::DCInteger>(_hndl);
    auto dcInt = __dcDm.getVar<dumisdk::DCInteger>(_hndl, intId);
    
    assert(dcInt->get() == 0);

    dcInt->set(20);

    assert(dcInt->get() == 20);
}

bool test_default_types(){
    register_default_types();
    test_default_assignment();
    //test_converters();

    return true;
}
