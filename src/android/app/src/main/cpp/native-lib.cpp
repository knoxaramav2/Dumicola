#include <jni.h>
#include <string>

#include "dumicore.h"
#include "utils.h"
#include "mobileLogger.h"
#include "jInterop.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_dumimobile_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

    InitDumiCore
    try{
        RegisterServices(([](serviceman::ServiceManager& sm){
            sm.registerLogger<AndroidLogger>();
        }));

        auto logger = GetLogger();
        logger->log("!!!");
        logger->log_debug("DEBUG");
        logger->log_info("INFO");
        logger->log_warn("WARNING");
        logger->log_error("ERROR");

    } catch(std::exception& e){
        printf("%s\n", e.what());
        fflush(stdout);
        return env->NewStringUTF("Ouch.");
    }

    return env->NewStringUTF("Static test");
}

