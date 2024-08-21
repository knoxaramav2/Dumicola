#include "tests.h"

#include "libManager.h"

dumisdk::LibraryManager* _libman;

void initFixtures(){
    _libman = new dumisdk::LibraryManager();
    _libman->load();
}

bool test_plugins(){

    assertNotThrows([](){
        initFixtures();

    });

    return true;
}