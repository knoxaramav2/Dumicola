#pragma once

#include <vector>
#include <mutex>

#include "bytecode.h"
#include "utils.h"
#include "environment.h"
#include "defs.h"

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

    class VALU{

        protected:

        public:

    };
    
    class VCPU{
        VALU _alu;
        std::string name;
        public:
        const APPSID cid;
        const HASHID hid;
        VCPU(std::string name);
        void update();
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


