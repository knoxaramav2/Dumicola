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

class T3: dumisdk::DCClass{

    std::string _name;

    public:
    T3(std::string name){ _name = name; }
    std::string getName(){return _name;}

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
    
    assertThrows([&converter]()->void{
        auto res = converter.convertAs<T1>(5.7);
    });

    printf("MARK");
}

void register_types(){

    std::string t3Name = "T3NameString";

    assertNotThrows([&](){
        dataman::__TypeManager tMan;
        // tMan.registerType<T3>([&t3Name](){
        //     return new T3(t3Name);
        // });
        tMan.registerType<T3>([&t3Name]() -> T3*{
            return new T3(t3Name);
        });
        auto t3 = tMan.create<T3>();
        assert(t3->getName() == t3Name);
    });

    
}

bool test_default_types(){


    register_types();
    test_converters();

    return true;
}
