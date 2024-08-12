#include "tests.hpp"
#include "fixtures.hpp"
#include "kassert.hpp"
#include <cstdio>

int main(){

    printf("Running test groups....\n");
    resetFixtures();

    test_default_types();
    test_misc();
    test_services();
    test_components();

    applyAsserts();

    const char*  exitMsg = testsFailed ? 
        "One or more tests failed" : "All tests passed";

    printf("%s\n", exitMsg);

    return testsFailed;
}