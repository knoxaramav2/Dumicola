//
// Created by knox on 8/9/24.
//

#include "jInterop.h"
#include <locale>

// std::string strFromJstr(JNIEnv* env, jstring jStr){
// if(!jStr){return "";}
// const jclass stringClass = env->GetObjectClass(jStr);
// const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
// const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

// size_t length = (size_t) env->GetArrayLength(stringJbytes);
// jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

// std::string ret = std::string((char *)pBytes, length);
// env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

// env->DeleteLocalRef(stringJbytes);
// env->DeleteLocalRef(stringClass);
// return ret;
// }

// std::string strToUtf8(std::string& str){
//     std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
//     std::wstring wideStr = converter.from_bytes(str);
//     std::string utf8Str = converter.to_bytes(wideStr);
//     return utf8Str;
// }