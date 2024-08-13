#include "tests.hpp"
#include "dumisdk.hpp"

class TestImp: public virtual dumisdk::IDCImplementation{

    public:
    TestImp(HASHID id, HASHID parentId):IDCDefinition(id, parentId){}
    int value = 1234;
};

class TestTempl: public virtual dumisdk::IDCTemplate<TestImp>{

    public:
    TestTempl(HASHID id, HASHID parentId, dumisdk::ComponentFactory<TestImp> factory):
        IDCTemplate(id, parentId, factory),IDCDefinition(id, parentId){}
    
};

void buildProvider(){
    
}

void interfaceItems(){

    assertNotThrows({
        TestTempl temp(0, 0, []()-> TestImp* {
            return new TestImp(0, 0);
        });
        auto inst = temp.create();
        assert(inst->value == 1234);
    });

    
}

bool test_components(){

    buildProvider();

    return true;
}