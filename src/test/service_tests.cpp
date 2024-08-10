#include "serviceman.hpp"
#include "kassert.hpp"

#include <stdio.h>

void testInstance();
void testSingelton();
void testCrossResolves();

serviceman::ServiceManager __servMan;

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

}

void testSingelton(){

}

void testCrossResolves(){
}

