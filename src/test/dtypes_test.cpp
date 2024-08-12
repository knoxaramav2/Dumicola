#include "dataman.hpp"
#include "kassert.hpp"
#include "stdio.h"
#include "tests.hpp"

dataman::DCDataManager __dcDm;

bool test_default_types(){

    auto intVarId = __dcDm.createVar(DC_INTEGER);
    auto deciVarId = __dcDm.createVar(DC_DECIMAL);
    auto boolVarId = __dcDm.createVar(DC_BOOL);
    auto stringVarId = __dcDm.createVar(DC_STRING);
    auto listVarId = __dcDm.createVar(DC_LIST);
    auto mapVarId = __dcDm.createVar(DC_MAP);

    assertLater(intVarId != 0);
    assertLater(deciVarId != 0);
    assertLater(boolVarId != 0);
    assertLater(stringVarId != 0);
    assertLater(listVarId != 0);
    assertLater(mapVarId != 0);

    assertLater(__dcDm.requestVar(intVarId) != nullptr);
    assertLater(__dcDm.requestVar(deciVarId) != nullptr);
    assertLater(__dcDm.requestVar(boolVarId) != nullptr);
    assertLater(__dcDm.requestVar(stringVarId) != nullptr);
    assertLater(__dcDm.requestVar(listVarId) != nullptr);
    assertLater(__dcDm.requestVar(mapVarId) != nullptr);

    assertLater(__dcDm.deleteVar(intVarId));
    assertLater(__dcDm.deleteVar(deciVarId));
    assertLater(__dcDm.deleteVar(boolVarId));
    assertLater(__dcDm.deleteVar(stringVarId));
    assertLater(__dcDm.deleteVar(listVarId));
    assertLater(__dcDm.deleteVar(mapVarId));

    assertLater(__dcDm.requestVar(intVarId) == nullptr);
    assertLater(__dcDm.requestVar(deciVarId) == nullptr);
    assertLater(__dcDm.requestVar(boolVarId) == nullptr);
    assertLater(__dcDm.requestVar(stringVarId) == nullptr);
    assertLater(__dcDm.requestVar(listVarId) == nullptr);
    assertLater(__dcDm.requestVar(mapVarId) == nullptr);

    return true;
}
