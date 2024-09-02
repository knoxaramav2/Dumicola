#pragma once

#include <vector>
#include <thread>

#include "instruction.h"

enum AluErr{
    OK,

    IDX_FAULT,              //Instruction or operands out of range

};

class VALU{

    void cmpUpdate(dumisdk::DCComponentImplementation&impl);

    public:

    void execute(InstSpace& ispace, CmpHeap& heap, int& counter, AluErr&error);
    VALU();
    ~VALU() = default;

};