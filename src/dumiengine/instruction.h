#pragma once

#include <map>
#include <tuple>
#include <vector>
#include "component.h"

enum DCInstruction{
    NOOP,       //Do Nothing

    UPDATE,     //[ID]  Call component update method

    WAITSIG,    //Wait for read lock release

    GOTO        //Jump to instruction index
};

struct Bytecode{
    //Acts as memory index 
    DCInstruction inst;
};

typedef std::vector<Bytecode> InstSpace;
typedef std::vector<dumisdk::DCComponentImplementation> CmpHeap;