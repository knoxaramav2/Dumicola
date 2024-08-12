#include "tests.hpp"
#include "dumisdk.hpp"

void buildProvider(){

    struct Provider: IDCProvider{
        public:
        Provider(){

        }
    };

    struct IProvider: DCProviderTemplate<Provider>{

    };
    
}

bool test_components(){

    buildProvider();

    return true;
}