#include "tests.hpp"
#include "dumisdk.hpp"

void buildProvider(){

    // struct Provider: IDCProvider{
    //     Provider(){

    //     }
    // };

    // struct IProvider: DCProviderTemplate<Provider>{
    //     IProvider(){

    //     }
    // };

    IDCField f("Test field", hashId(""));
    DCConfigField("Config field", hashId(""));
    printf("No exception for IDCField\n");
    
}

bool test_components(){

    buildProvider();

    return true;
}