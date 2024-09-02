#pragma once

#include <vector>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <atomic>
#include <cstdarg>
#include <sys/types.h>
#include <fcntl.h>
#include <semaphore>

#include "utils.h"
#include "environment.h"
#include "defs.h"
#include "alu.h"
#include "component.h"

namespace dumiengine{

#ifdef PLATFORM_WINDOWS

#elif defined(PLATFORM_GNU)

#elif defined(PLATFORM_ANDROID)

#endif
    
    enum DCEngState{
        STOP, PAUSE, RUN
    };

    //TODO Enable multiprocess support
    enum DCCncMode{
        PROCESS, THREAD
    };
    
    class VCPU{
        VALU _alu;
        InstSpace _instSpace;
        int _pc;
        CmpHeap _cmpMemHeap;
        std::string name;
        bool _waitsig;

        protected:
        AluErr _error;
        friend class DumiEngine;

        public:
        const APPSID cid;
        const HASHID hid;
        VCPU(std::string name);
        bool update();
    };

    class DumiEngine{
        DCEngState _state;
        const DCCncMode _cncMode;
        std::vector<VCPU> _vcpus;
        std::vector<std::thread> _threads;
        std::mutex _mux;
        std::condition_variable _cv;
        std::atomic<bool> _running;

        void _startCore(VCPU& vcpu);
        void _stopCore(VCPU& vcpu);

        void _runVCPU(VCPU& vcpu);
        void _addVCPU();

        void _handleVCPUFault(VCPU& vcpu);

        public:

        //DumiEngine(DCCncMode mode, unsigned numVCpu);
        DumiEngine(unsigned numVCpu);
        ~DumiEngine();

        bool setState(DCEngState state);
        void update();

        APPSID addCore(const char* name="");
        bool destroyCore(APPSID id);
        bool destroyCore(const char* name);
    };
};


