#pragma once

#include <string>
#include <atomic>
#include <functional>

#include "alu.h"

namespace dumiengine{
        class ProgramBlock{

        CmpHeap _heap;
        InstSpace _instSpace;

        int _pc; //program counter
        AluErr _err;
        std::atomic<bool> _running;

        unsigned _msDel; //millisecond delay

        using FaultCallback = std::function<void(APPSID)>;
        FaultCallback _faultCallback;
        friend class DumiEngine;

        void _load(std::string& prgData);
        void _update();
        void _loop();

        public:

        ProgramBlock(std::string& prgData, FaultCallback callback);
        void stop();
        void start();
    };
}