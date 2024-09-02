#include "alu.h"

//Map instructions to argument count
std::map<DCInstruction, std::tuple<int>> AluLookup{
    {NOOP, (0)},

    {UPDATE, (1)},

    {WAITSIG, (0)},

    {GOTO, (1)}
};

void VALU::cmpUpdate(dumisdk::DCComponentImplementation &impl)
{
}

void VALU::execute(InstSpace &ispace, CmpHeap &heap,
                   int &counter, AluErr &error)
{
    if (counter >=  ispace.size() || counter+ispace[counter].inst){
        error = IDX_FAULT;
        return;
    }

    switch (ispace[counter].inst)
    {
    case NOOP:break;

    case UPDATE:

        break;
    case WAITSIG:
        break;
    case GOTO:
        break;
    
    default:
        break;
    }
}

VALU::VALU()
{

}