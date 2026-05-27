/**
 * Created by Aaron Lee on 2021/11/19.
 * JNI工具类，用于统一封装JNI的公共功能函数
 * 1、动态注册JNI函数
 * 2、注销动态注册的JNI函数
 *
 */

#ifndef INKPAINT_JNITOOLS_H
#define INKPAINT_JNITOOLS_H

#include <jni.h>
#include <map>
#include <any>

std::map<std::string, std::any> converMapJava2Cpp(JNIEnv *env, jobject commands);

jobject convertCppMapToJavaMap(JNIEnv* env, const std::map<std::string, std::any> &cppMap);

#endif // INKPAINT_JNITOOLS_H
