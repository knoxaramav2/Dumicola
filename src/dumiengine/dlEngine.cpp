#include "dlEngine.h"

#define LOCK_GAURD std::lock_guard<std::mutex> lock(_mux);

dumiengine::DumiEngine::DumiEngine()
{
}

dumiengine::DumiEngine::~DumiEngine(){
    stop();
    for(auto& [id, tuple]: _tPrgs){
        auto& [thread, block] = tuple;
        if(thread.joinable()){
            thread.join();
        }
        delete block;
    }
    _tPrgs.clear();
}

void dumiengine::DumiEngine::start()
{
    for(auto& [id, tuple]: _tPrgs){
        auto& [thread, block] = tuple;
        block->start();
    }
}

void dumiengine::DumiEngine::stop()
{
    for(auto& [id, tuple]: _tPrgs){
        auto& [thread, block] = tuple;
        block->stop();
    }
}

APPSID dumiengine::DumiEngine::loadDCProgram(std::string &prgData)
{
    auto callback = [this](APPSID id){
        this->_eFaultHndl(id);
    };
    ProgramBlock* pblk = new ProgramBlock(prgData, callback);
    std::thread bthread(&ProgramBlock::_loop, pblk);
    APPSID id = appId(pblk);
    _tPrgs[id] = std::make_tuple(std::move(bthread), pblk);

    return id;
}

void dumiengine::DumiEngine::_eFaultHndl(APPSID id)
{
    std::lock_guard<std::mutex> lock(_mux);
    auto it = _tPrgs.find(id);
    if (it == _tPrgs.end()){
        //TODO State disorder
        return;
    }

    printf("Terminate program %ld%s", id, NL);

    auto& [thread, block] = it->second;
    block->stop();

    //TODO Program rescue

    if(thread.joinable()){ thread.join(); }
    delete block;
    _tPrgs.erase(it);

}

