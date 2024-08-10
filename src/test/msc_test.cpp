#include <stdio.h>
#include "utils.hpp"

int main(int argc, char** argv){

    auto nstr = frmstr("TEST:: %s (%d)\n", __FILE__, __LINE__).c_str();
    printf("MISC. TESTS | %s\n", nstr);

    return 0;
}