#include <stdio.h>

#include "tests.h"
#include "environment.h"
#include "dumilang.h"
#include "dccompile.h"
#include "dc_file.h"

void init_lang(){
    
}

static std::vector<Bytecode> loadProg(std::string path){
    
    auto fpath = dcutil::rootDir()/"scripts/test"/path;
    auto data = dcutil::readFileAsString(fpath);
    return compile(data);
}

static void test_cores(){

    assertNotThrows([]{
        loadProg("program1.dc");
    });
}

bool test_dumilang(){

    init_lang();
    printf("With src: %s%s", DCLANG_DEV_SRC, NL);

    loadProg("program1.dc");
    
    return true;
}