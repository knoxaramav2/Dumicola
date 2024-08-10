#include <jni.h>
#include <string>

#include "dumicore.hpp"
#include "utils.hpp"
#include "mobileLogger.h"
#include "jInterop.h"
#include <android/log.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_dumimobile_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    InitDumiCore
    RegisterServices([](serviceman::ServiceManager& sm){
        __android_log_print(ANDROID_LOG_INFO, "DUMICOLA", "Init logger");
        sm.registerLogger<DesktopLogger>();
    });

    try{
        auto p = GetLogger();
        auto d = static_cast<Logger*>(p.get());
        auto b = dynamic_cast<Logger*>(p.get());
        p->log("!");
    } catch (std::exception& e){
        __android_log_print(ANDROID_LOG_INFO, "DUMICOLA", "EX: %s", e.what());
    }



    //logger->log("Call from Dumimobile");

    auto format = frmstr("Hello, %s", "Knox@");
    //std::string hello(frmstr("Hello %s world", "blue"));
    //std::string utf8 = strToUtf8("Hello");

    //auto utf8 = testStr();

    return env->NewStringUTF(format.c_str());
}

