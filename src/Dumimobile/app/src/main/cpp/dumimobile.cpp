#include <jni.h>
#include <string>
#include <android/log.h>

#include "dumicore.hpp"
#include "utils.hpp"
#include "mobileLogger.h"
//#include "jInterop.h"

extern "C"
JNIEXPORT jint JNICALL
Java_com_knx_dumimobile_ui_home_HomeFragment_InitDumicore(JNIEnv *env, jobject ) {

    static bool _started = false;
    if(_started){ return 0; }
    _started = true;

    InitDumiCore
    RegisterServices(([](serviceman::ServiceManager& sm){
        sm.registerSingelton<dumisdk::ILogger, AndroidLogger>();
    }));

    __android_log_print(ANDROID_LOG_DEBUG, "DUMICOLA", "%s", "CORE INIT");

    GetLogger()->log_debug("Core start");

    return 1;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_knx_dumimobile_ui_home_HomeFragment_LogStatic(JNIEnv *env, jobject){
    //auto logger = GetLogger();
    //auto ptr = (AndroidLogger*)&(*logger);
    try{
        static int c = 0;
        __android_log_print(ANDROID_LOG_INFO, "DUMICOLA", "%s %d", "COUNTER: ", ++c);
        auto logger = dumicore::__core_inst->getLogger();
        logger->log_info("HELLO ");
    } catch (std::exception &e){
        __android_log_print(ANDROID_LOG_INFO, "DUMICOLA", "%s %s", "Exception: ", e.what());
    }

    return 0;
}
