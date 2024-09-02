#pragma once

#include <vector>
#include <string>
#include <tuple>
#include <condition_variable>
#include <atomic>
#include <sys/types.h>

#include "libManager.h"
#include "alu.h"
#include "programblock.h"

namespace dumiengine{

    class DumiEngine{
        
        VALU _alu;
        std::map<APPSID, std::tuple<std::thread, ProgramBlock*>>
            _tPrgs;
        void _eFaultHndl(APPSID id);
        std::mutex _mux;
        public:

        DumiEngine();
        ~DumiEngine();

        void start();
        void stop();

        APPSID loadDCProgram(std::string& prgData);

    };
}