#include "tests.h"
#include "fixtures.h"
#include "kassert.h"
#include <cstdio>

int main(){

    printf("Running test groups....\n");
    resetFixtures();

    test_default_types();
    test_misc();
    test_services();
    test_components();
    test_plugins();
    test_dumilang();
    test_engine();

    applyAsserts();

    const char*  exitMsg = testsFailed ? 
        "One or more tests failed" : "All tests passed";

    printf("%s\n", exitMsg);

    return testsFailed;
}