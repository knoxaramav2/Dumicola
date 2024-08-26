#include <stdio.h>

#include "tests.h"
#include "environment.h"
#include "dumilang.h"

void init_lang(){
    
}

bool test_dumilang(){

    init_lang();
    printf("With src: %s%s", DCLANG_DEV_SRC, NL);

    
    return true;
}