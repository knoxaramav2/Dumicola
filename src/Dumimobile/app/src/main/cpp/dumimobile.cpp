#include <jni.h>
#include <string>

#include "dumicore.hpp"
#include "utils.hpp"
#include "mobileLogger.h"
//#include "jInterop.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_dumimobile_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

//    InitDumiCore
//            dumicore::DumiCore::registerServices([](serviceman::ServiceManager& sm){
//        sm.registerSingelton<dumisdk::ILogger, AndroidLogger>();
//    });
//
//    auto logger = dumicore::DumiCore::getLogger();
//    logger->log_debug("Debug line: %s", __FILE_NAME__);

    return env->NewStringUTF("Static test");
}

