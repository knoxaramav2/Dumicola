#include "dumisdk.hpp"
#include "kassert.hpp"
#include "stdio.h"

dumisdk::__internal::DCDataManager __dcDm;

void test_default_types(){

    auto intVarId = __dcDm.createVar(DC_INTEGER);
    auto deciVarId = __dcDm.createVar(DC_DECIMAL);
    auto boolVarId = __dcDm.createVar(DC_BOOL);
    auto stringVarId = __dcDm.createVar(DC_STRING);
    auto listVarId = __dcDm.createVar(DC_LIST);
    auto mapVarId = __dcDm.createVar(DC_MAP);

    KTEST::assertLater(intVarId != 0);
    KTEST::assertLater(deciVarId != 0);
    KTEST::assertLater(boolVarId != 0);
    KTEST::assertLater(stringVarId != 0);
    KTEST::assertLater(listVarId != 0);
    KTEST::assertLater(mapVarId != 0);

    KTEST::assertLater(__dcDm.requestVar(intVarId) != nullptr);
    KTEST::assertLater(__dcDm.requestVar(deciVarId) != nullptr);
    KTEST::assertLater(__dcDm.requestVar(boolVarId) != nullptr);
    KTEST::assertLater(__dcDm.requestVar(stringVarId) != nullptr);
    KTEST::assertLater(__dcDm.requestVar(listVarId) != nullptr);
    KTEST::assertLater(__dcDm.requestVar(mapVarId) != nullptr);

    KTEST::assertLater(__dcDm.deleteVar(intVarId));
    KTEST::assertLater(__dcDm.deleteVar(deciVarId));
    KTEST::assertLater(__dcDm.deleteVar(boolVarId));
    KTEST::assertLater(__dcDm.deleteVar(stringVarId));
    KTEST::assertLater(__dcDm.deleteVar(listVarId));
    KTEST::assertLater(__dcDm.deleteVar(mapVarId));

    KTEST::assertLater(__dcDm.requestVar(intVarId) == nullptr);
    KTEST::assertLater(__dcDm.requestVar(deciVarId) == nullptr);
    KTEST::assertLater(__dcDm.requestVar(boolVarId) == nullptr);
    KTEST::assertLater(__dcDm.requestVar(stringVarId) == nullptr);
    KTEST::assertLater(__dcDm.requestVar(listVarId) == nullptr);
    KTEST::assertLater(__dcDm.requestVar(mapVarId) == nullptr);
}

int main(){
    test_default_types();

    KTEST::applyAsserts();

    return 0;
}