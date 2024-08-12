#include "fixtures.hpp"

FixtureControl* __fixtures = nullptr;

void resetFixtures()
{
    if(__fixtures != nullptr){
        delete __fixtures;
    }
    __fixtures = new FixtureControl();
}

FixtureControl::FixtureControl()
{
    InitDumiCore
    __core = dumicore::__core_inst;
}

FixtureControl::~FixtureControl()
{
    Shutdown
}
