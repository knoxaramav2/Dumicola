#include "programblock.h"
#include "dc_string.h"
#include "dccompile.h"

void dumiengine::ProgramBlock::_load(std::string &prgData)
{
    _instSpace = compile(prgData);
    //TODO Error handling
}

dumiengine::ProgramBlock::ProgramBlock(std::string &prgData, FaultCallback callback):
    _faultCallback(callback),
    _running(true), _msDel(100), _pc(0)
{
    _load(prgData);
}

void dumiengine::ProgramBlock::stop()
{
    _running.store(false);
}

void dumiengine::ProgramBlock::start()
{
    _running.store(true);
}

void dumiengine::ProgramBlock::_loop()
{
    while(_running.load()){
        _update();
        std::this_thread::sleep_for(std::chrono::milliseconds(_msDel));
    }
}

void dumiengine::ProgramBlock::_update()
{
}
