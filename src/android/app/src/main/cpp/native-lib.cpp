#include <jni.h>
#include "dumicore.hpp"
#include "dc_string.hpp"
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_dumimobile_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    InitDumiCore
    std::string hello = frmstr("Hello %s world", "blue");
    return env->NewStringUTF(hello.c_str());
}
