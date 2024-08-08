#include "serviceman.hpp"
#include "kassert.hpp"

void testInstance();
void testSingelton();

serviceman::ServiceManager* __servMan;

struct IDataType{
    const char* _msgType;
    int loc;
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

void initFixtures(){

    __servMan = new serviceman::ServiceManager();
}

int main(){

    initFixtures();

    printf("START TESTS\n\n");

    testSingelton();
    testInstance();

    printf("\n\nEND TESTS\n");

    delete __servMan;

    return KTEST::testsFailed;
}


void testInstance(){
    KTEST::assert((__servMan->registerInstance<IDataType, Instance1>()));
    KTEST::assert((__servMan->registerInstance<Instance2>()));
}

void testSingelton(){
    KTEST::assert((__servMan->registerSingelton<IDataType, Singelton1>()));
    KTEST::assert((__servMan->registerSingelton<Singelton2>()));
}

