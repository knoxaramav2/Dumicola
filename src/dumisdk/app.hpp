#pragma once

#include "dtypes.hpp"

namespace dumisdk
{
    class IDumiApp{
        
        protected:
        virtual void onCreate() = 0;
        virtual void onBuild() = 0;
        virtual void onStart() = 0;
        virtual void onPause() = 0;
        virtual void onStop() = 0;
        
        public:
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void pause() = 0;
    };

    class IAppContainer{        
        protected:
        
        public:

    };
}
