#include "serviceman.hpp"
#include "kassert.hpp"

void singeltonTests();

serviceman::ServiceManager* __servMan;

void initFixtures(){

    //instance

    //scopes

    //lifetime

}

int main(){

    int a = 5;

    initFixtures();


    singeltonTests();

    return KTEST::testsFailed;
}

struct scope{
    scope(){ printf("SCOPE_BEGIN\n"); }
    ~scope(){ printf("SCOPE_END\n"); }
    void speak(){printf("SCOPE FUNCTION CALLED\n");}
};

class ScopeTest{

    public:

    ScopeTest(){ printf("SCOPETEST_BEGIN\n"); }
    ~ScopeTest(){ printf("SCOPETEST_END\n"); }

    scope requestScope(){
        return scope();
    }

};

void singeltonTests(){
    
    serviceman::ServiceManager sMan;
    sMan.registerSingelton<scope>();
    printf(":: A\n");
    auto scp = sMan.resolveService<scope>();
    printf(":: B\n");
    scp->speak();
    printf("OTHER STUFF\n");

}