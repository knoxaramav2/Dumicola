#include <jni.h>
#include <string>
#include <android/log.h>

#include "dumicore.hpp"
#include "utils.hpp"
#include "mobileLogger.h"
//#include "jInterop.h"

extern "C"
JNIEXPORT int JNICALL
Java_com_knx_dumimobile_MainActivity_initDumiCore(JNIEnv *env, jobject thiz) {

    static bool _started = false;
    if(_started){ return 1; }
    _started = true;

    InitDumiCore
    RegisterServices(([](serviceman::ServiceManager& sm){
        sm.registerSingelton<dumisdk::ILogger, AndroidLogger>();
    }));

    return 0;
}