#include "serviceman.hpp"
#include "kassert.hpp"
#include "tests.hpp"

#include <cstdio>

void testInstance();
void testSingelton();
void testCrossResolves();

serviceman::ServiceManager __servMan;

struct StructBase{
    public:
    virtual ~StructBase() = default;
    virtual const char* speak() = 0;
};

struct Struct1: public StructBase {
    Struct1(const char* msg):msg(msg){}
    const char* msg;

    const char* speak() override {
        //printf("%s\n", msg);
        return msg;
    }
};

struct NoRegister{};

void initFixtures(){

    
}

bool test_services(){

    initFixtures();

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
    std::function<Struct1*(const char*)> fnc = [](const char* name) -> Struct1* {
            return new Struct1(name);
    };
    const char* sname1 = "TestNameA1";
    const char* sname2 = "TestNameA2";
    __servMan.addTransient<StructBase, Struct1, const char*>(fnc);
    __servMan.addTransient<Struct1, const char*>(fnc);
    auto s1 = __servMan.resolveTransientAs<StructBase>(sname1);
    auto s2 = __servMan.resolveTransientAs<StructBase>(sname2);
    assert(s1 != nullptr);
    assert(strlen(s1->speak()) == strlen(sname1));
    assert(strlen(s2->speak()) == strlen(sname2));
}


void testSingelton(){

}

void testCrossResolves(){
}

