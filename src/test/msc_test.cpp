#include <stdio.h>
#include "dc_string.hpp"

int main(int argc, char** argv){

    auto nstr = frmstr("TEST:: %s (%d)\n", __FILE__, __LINE__);
    printf("MISC. TESTS | %s\n", nstr.c_str());

    return 0;
}