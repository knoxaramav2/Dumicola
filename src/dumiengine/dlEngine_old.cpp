#include "dlEngine_old.h"
#include "dumiexcept.h"

#define LOCK_GAURD std::lock_guard<std::mutex> lock(_mux);

#pragma region PARALLEL_CONTROLS
#ifdef PLATFORM_WINDOWS
void dumiengine::DumiEngine::_startCore(VCPU& vcpu){

}

void dumiengine::DumiEngine::_stopCore(VCPU& vcpu){

}

#elif defined(PLATFORM_GNU)

void dumiengine::DumiEngine::_startCore(VCPU& vcpu){

}

void dumiengine::DumiEngine::_stopCore(VCPU& vcpu){

}

//else if (_cncMode == PROCESS) {
//            for(auto& vcpu: _vcpus){
//                pid_t pid = fork();
//                if(pid == 0){
//                    // Child process
//                    _runVCPU(vcpu);
//                    exit(0);
//                } else if(pid > 0){
//                    // Parent process
//                    _pids.push_back(pid);
//                } else {
//                    // Fork failed
//                    throw dumisdk::dumiexception("Failed to fork process");
//                }
//            }
//        }

//else if (_cncMode == PROCESS) {
//            for(auto pid: _pids){
//                kill(pid, SIGTERM);
//                waitpid(pid, nullptr, 0);
//            }
//            _pids.clear();

#elif defined(PLATFORM_ANDROID)

void dumiengine::DumiEngine::_startCore(VCPU& vcpu){

}

void dumiengine::DumiEngine::_stopCore(VCPU& vcpu){

}

#endif
#pragma endregion

void dumiengine::DumiEngine::_runVCPU(VCPU &vcpu)
{
    while(_running){
        std::unique_lock<std::mutex> lock(_mux);
        _cv.wait(lock, [this]{ return _state == RUN || !_running; });

        if(!_running){ break; }

        if(_state == RUN){
            if (vcpu.update()){ //FAULT
                _handleVCPUFault(vcpu);

            }
        } else if (_state == PAUSE){
            _cv.wait(lock, [this] { return _state == RUN || !_running; });
        }

    }
}

void dumiengine::DumiEngine::_addVCPU()
{
    LOCK_GAURD
    auto name = dcutil::frmstr("VCPU_%d", (int)_vcpus.size());
    _vcpus.push_back(VCPU(name.c_str()));
}

void dumiengine::DumiEngine::_handleVCPUFault(VCPU &vcpu)
{
    //TODO Handle by error
    //AluErr err = vcpu._error...
    
}

//dumiengine::DumiEngine::DumiEngine(DCCncMode mode, unsigned numVCpu) :
dumiengine::DumiEngine::DumiEngine(unsigned numVCpu) :
    _cncMode(THREAD), _state(STOP), _running(false)
{
    //TODO by configuration
     if(numVCpu > 8){
         throw dumisdk::dumiexception("Dumiengine virtual core limit exceeded (8)");
     }

     for(unsigned i = 0; i < numVCpu; ++i){
         _addVCPU();
     }
}

dumiengine::DumiEngine::~DumiEngine()
{
    printf("End engine%s", NL);
    setState(STOP);
}

bool dumiengine::DumiEngine::setState(DCEngState state)
{
    LOCK_GAURD

    if(state == RUN){
        if(_state == RUN) { return false; }
        _state = RUN;
        _running = true;

        for(auto& vcpu: _vcpus){
            if(_cncMode == THREAD){
                _threads.emplace_back(&DumiEngine::_runVCPU, this, std::ref(vcpu));
            } else {
                _startCore(vcpu);
            }
        }

    } else if (state == PAUSE){
        if(_state == PAUSE){ return false; }
        _state = PAUSE;
    } else if (state == STOP){
        if(_state == STOP) { return false; }
        _state = STOP;
        _running = false;
        _cv.notify_all();

        if(_cncMode == THREAD){
             for(auto& thread: _threads){
                if(thread.joinable()){
                    thread.join();
                }
            }
            _threads.clear();
        } else {
            for(auto& vcpu: _vcpus){
                _stopCore(vcpu);
            }
        }
       
    } else {
        throw dumisdk::dumiexception("Invalid DumiEngine state");
    }

    return true;
}

void dumiengine::DumiEngine::update()
{
    std::unique_lock<std::mutex> lock(_mux);
    _cv.notify_all();
}

dumiengine::VCPU::VCPU(std::string name):name(name),
    cid(appId(this)), hid(hashId(name)){
    printf(":> INIT %s%s", name.c_str(), NL);
}

bool dumiengine::VCPU::update()
{
    if(_error){
        //TODO Fault state: stop/hang VCPU process/thread
        printf("VCPU ERR: %d%s", _error, NL);
        return true;
    } else {
        _alu.execute(_instSpace, _cmpMemHeap, _pc, _error);
    }

    return false;
}
