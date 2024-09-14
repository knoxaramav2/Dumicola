#include "serviceman.h"
#include "kassert.h"
#include "tests.h"

#include <cstdio>

void testInstance();
void testSingelton();
void testCrossResolves();

serviceman::ServiceManager __servMan;

struct StructBase{
    public:
    virtual ~StructBase() = default;
    StructBase(const char* msg):_msg(msg){
        printf("SB ADDR: %p \n", _msg);
    }
    virtual const char* speak() = 0;
    //protected:
    const char* _msg;
};

struct Struct1: public StructBase {
    Struct1(const char* msg):StructBase(msg){
        printf("STR1 ADD: %p | %s\n", _msg, msg);
    }

    const char* speak() override {
        printf("%s\n", _msg);
        return _msg;
    }
};

std::function<Struct1*(const char*)> fnc = [](const char* name) -> Struct1* {
    printf("FNC ADDR: %p | %s\n", name, name);
    return new Struct1(name);
};

struct NoRegister{};

bool test_services(){

    printf("START TESTS\n\n");

    assertNotThrows([](){
        testSingelton();
        testInstance();
        testCrossResolves();
    });

    printf("\n\nEND TESTS\n");

    return testsFailed;
}

void testInstance() {
    const char* sname1 = "TestNameA1";
    const char* sname2 = "TestNameA2";
    __servMan.registerTransient<StructBase, Struct1, const char*>(fnc);
    __servMan.registerTransient<Struct1, const char*>(fnc);
    auto s1 = __servMan.resolveTransientAs<StructBase>(sname1);
    auto s2 = __servMan.resolveTransientAs<StructBase>(sname2);
    assert(s1 != nullptr);
    assert(s2 != nullptr);
    assert(strlen(s1->speak()) == strlen(sname1));
    assert(strlen(s2->speak()) == strlen(sname2));
}


void testSingelton(){

    const char* sing1 = "Singleton1";
    const char* sing2 = "Singleton2";

     __servMan.registerSingleton<StructBase, Struct1, const char*>(fnc);
     __servMan.registerSingleton<Struct1, const char*>(fnc);

     auto sid1 = __servMan.createSingletonAs<StructBase>(sing1);
     auto sid2 = __servMan.createSingletonAs<Struct1>(sing2);

     auto sg1 = (Struct1*)__servMan.resolveSingletonAs<StructBase>(sid1);
     auto sg2 = __servMan.resolveSingletonAs<Struct1>(sid2);

    assert(sg1 != nullptr);
    assert(sg2 != nullptr);
    assert(strlen(sg1->speak()) == strlen(sing1));
    assert(strlen(sg2->speak()) == strlen(sing2));
}

void testCrossResolves(){
}

