#include "tests.hpp"
#include "dumisdk.hpp"

class TestImp: public virtual dumisdk::IDCComp{

    public:
    TestImp(HASHID id, HASHID parentId):IDCCompDef(id, parentId){}
    int value = 1234;
};

class TestTempl: public virtual dumisdk::IDCCompTemplate<TestImp>{

    public:
    TestTempl(HASHID id, HASHID parentId, dumisdk::ComponentFactory<TestImp> factory):
        IDCCompTemplate(id, parentId, factory),IDCCompDef(id, parentId){}
    
};

void buildProvider(){
    TestTempl temp(0, 0, []()-> TestImp* {
        return new TestImp(0, 0);
    });
    auto inst = temp.create();
    assert(inst->value == 1234);
}

bool test_components(){

    buildProvider();

    return true;
}