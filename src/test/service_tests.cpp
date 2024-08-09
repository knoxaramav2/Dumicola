#include "serviceman.hpp"
#include "kassert.hpp"

#include <stdio.h>

void testInstance();
void testSingelton();
void testCrossResolves();

serviceman::ServiceManager __servMan;

struct IDataType{
    const char* _msgType;
    int loc;
    IDataType(): IDataType("IDefaultType"){};
    IDataType(const char* msg): _msgType(msg){
        static int sValue = 1;
        loc = sValue++;
        printf("+ %s(%d) @ %lx\n", _msgType, loc, appId(this));
    }
    ~IDataType(){ printf("- %s(%d) @ %lx\n", _msgType, loc, appId(this)); }

};

struct Singelton1 : public IDataType{
    Singelton1(): IDataType("SINGELTON1"){}
};

struct Singelton2 : public IDataType{
    Singelton2(): IDataType("SINGELTON2"){}
};

// struct Scoped: public DataType{
//     Scoped(): DataType("SCOPED"){}
// };

struct Instance1: public IDataType{
    Instance1(): IDataType("INSTANCE1"){}
};

struct Instance2: public IDataType{
    Instance2(): IDataType("INSTANCE2"){}
};

struct NoRegister{};

void initFixtures(){

    
}

int main(){

    initFixtures();

    printf("START TESTS\n\n");

    testSingelton();
    testInstance();
    testCrossResolves();

    printf("\n\nEND TESTS\n");

    return testsFailed;
}


void testInstance(){
    assert((__servMan.registerInstance<IDataType, Instance1>()));
    assert((__servMan.registerInstance<Instance2>()));

    assertThrows(__servMan.resolveServiceInstance<NoRegister>());

    assertNotThrows(__servMan.resolveServiceInstance<Instance1>());
    assertNotThrows(__servMan.resolveServiceInstance<Instance2>());

    assertThrows(__servMan.resolveServiceInstance<IDataType>());
}

void testSingelton(){

    assert((__servMan.registerSingelton<IDataType, Singelton1>()));
    assert((__servMan.registerSingelton<Singelton2>()));

    assertThrows((__servMan.resolveServiceInstance<Singelton1>()));
    assertThrows((__servMan.resolveServiceSingelton<Instance1>()));

    assertThrows(__servMan.resolveServiceSingelton<NoRegister>());

    assertNotThrows(__servMan.resolveServiceSingelton<Singelton1>());
    assertNotThrows(__servMan.resolveServiceSingelton<Singelton2>());
}

void testCrossResolves(){
    assertThrows(__servMan.resolveServiceSingelton<Instance1>());
    assertThrows(__servMan.resolveServiceInstance<Singelton1>());
}

