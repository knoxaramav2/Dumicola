#include "dataman.hpp"
#include "kassert.hpp"
#include "stdio.h"
#include "tests.hpp"

dataman::DataManager __dcDm;

class T1: dumisdk::DCLiteral{
    public:
    T1(int v):value(v){}
    int value;
};

class T2: dumisdk::DCLiteral{
    public:
    T2(float v):value(v){}
    float value;
};

void test_converters(){

    auto converter = __dcDm.getConverter();

    assertNotThrows(([&converter](){
        converter.addConverter<T1, T2>([](T2 val)->T1{
            return T1((int)val.value);
        });

        T2 t2(8.4);
        T1 ti = converter.convertAs<T1>(t2);

        assert(ti.value == 8);
    }));

    assertThrows(([&converter](){
        converter.convertAs<T1>(5.7);
    }));

    
}

bool test_default_types(){

    test_converters();

    return true;
}
