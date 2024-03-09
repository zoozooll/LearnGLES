//
// Created by huion on 2024/3/9.
//

#include "SceneCommand.h"

#include <jni.h>
#include <map>
#include <any>
#include <string>
#include <vector>

extern "C"
JNIEXPORT void JNICALL
Java_com_example_learngles_NativeLibHelper_sendCommands(JNIEnv *env, jclass clazz,
        jobject commands) {
    jclass mapClass = env->FindClass("java/util/Map");
    jmethodID entrySetMethod = env->GetMethodID(mapClass, "entrySet", "()Ljava/util/Set;");
    jobject entrySet = env->CallObjectMethod(commands, entrySetMethod);

    jclass setClass = env->FindClass("java/util/Set");
    jmethodID iteratorMethod = env->GetMethodID(setClass, "iterator", "()Ljava/util/Iterator;");
    jobject iterator = env->CallObjectMethod(entrySet, iteratorMethod);

    jclass iteratorClass = env->FindClass("java/util/Iterator");
    jmethodID hasNextMethod = env->GetMethodID(iteratorClass, "hasNext", "()Z");
    jmethodID nextMethod = env->GetMethodID(iteratorClass, "next", "()Ljava/lang/Object;");

    // C++ std::map to store the converted values
    std::map<std::string, std::any> cppMap;

    while (env->CallBooleanMethod(iterator, hasNextMethod)) {
        jobject entry = env->CallObjectMethod(iterator, nextMethod);

        jclass entryClass = env->FindClass("java/util/Map$Entry");
        jmethodID getKeyMethod = env->GetMethodID(entryClass, "getKey", "()Ljava/lang/Object;");
        jmethodID getValueMethod = env->GetMethodID(entryClass, "getValue", "()Ljava/lang/Object;");

        jstring javaKey = (jstring)env->CallObjectMethod(entry, getKeyMethod);
        jobject javaValue = env->CallObjectMethod(entry, getValueMethod);

        const char *cKey = env->GetStringUTFChars(javaKey, nullptr);

        if (env->IsInstanceOf(javaValue, env->FindClass("java/lang/Byte"))) {
            jbyte value = env->CallByteMethod(javaValue, env->GetMethodID(env->FindClass("java/lang/Byte"), "byteValue", "()B"));
            cppMap[cKey] = static_cast<char>(value);
        } else if (env->IsInstanceOf(javaValue, env->FindClass("java/lang/Short"))) {
            jshort value = env->CallShortMethod(javaValue, env->GetMethodID(env->FindClass("java/lang/Short"), "shortValue", "()S"));
            cppMap[cKey] = static_cast<int16_t >(value);
        } else if (env->IsInstanceOf(javaValue, env->FindClass("java/lang/Integer"))) {
            jint value = env->CallIntMethod(javaValue, env->GetMethodID(env->FindClass("java/lang/Integer"), "intValue", "()I"));
            cppMap[cKey] = static_cast<int>(value);
        } else if (env->IsInstanceOf(javaValue, env->FindClass("java/lang/Long"))) {
            jlong value = env->CallLongMethod(javaValue, env->GetMethodID(env->FindClass("java/lang/Long"), "longValue", "()J"));
            cppMap[cKey] = static_cast<int64_t>(value);
        } else if (env->IsInstanceOf(javaValue, env->FindClass("java/lang/Float"))) {
            jfloat value = env->CallFloatMethod(javaValue, env->GetMethodID(env->FindClass("java/lang/Float"), "floatValue", "()F"));
            cppMap[cKey] = static_cast<float>(value);
        } else if (env->IsInstanceOf(javaValue, env->FindClass("java/lang/Double"))) {
            jdouble value = env->CallDoubleMethod(javaValue, env->GetMethodID(env->FindClass("java/lang/Double"), "doubleValue", "()D"));
            cppMap[cKey] = static_cast<double>(value);
        } else if (env->IsInstanceOf(javaValue, env->FindClass("java/lang/Boolean"))) {
            jboolean value = env->CallBooleanMethod(javaValue, env->GetMethodID(env->FindClass("java/lang/Boolean"), "booleanValue", "()Z"));
            cppMap[cKey] = static_cast<bool>(value);
        } else if (env->IsInstanceOf(javaValue, env->FindClass("java/lang/String"))) {
            const char *stringValue = env->GetStringUTFChars((jstring)javaValue, nullptr);
            cppMap[cKey] = std::string(stringValue);
            env->ReleaseStringUTFChars((jstring)javaValue, stringValue);
        } else if (env->IsInstanceOf(javaValue, env->FindClass("[B"))) {
            // Handle byte array
            jbyteArray value = reinterpret_cast<jbyteArray>(javaValue);
            jsize length = env->GetArrayLength(value);
            jbyte *byteArrayElements = env->GetByteArrayElements(value, nullptr);
            std::vector<char> cppByteArray(byteArrayElements, byteArrayElements + length);
            env->ReleaseByteArrayElements(value, byteArrayElements, JNI_ABORT); // JNI_ABORT to avoid copying back changes
            cppMap[cKey] = cppByteArray;
        } else if (env->IsInstanceOf(javaValue, env->FindClass("[S"))) {
            // Handle byte array
            jshortArray value = reinterpret_cast<jshortArray>(javaValue);
            jsize length = env->GetArrayLength(value);
            jshort *arrayElements = env->GetShortArrayElements(value, nullptr);
            std::vector<int16_t> cppArray(arrayElements, arrayElements + length);
            env->ReleaseShortArrayElements(value, arrayElements, JNI_ABORT); // JNI_ABORT to avoid copying back changes
            cppMap[cKey] = cppArray;
        } else if (env->IsInstanceOf(javaValue, env->FindClass("[J"))) {
            // Handle byte array
            jlongArray value = reinterpret_cast<jlongArray>(javaValue);
            jsize length = env->GetArrayLength(value);
            jlong *longArrayElements = env->GetLongArrayElements(value, nullptr);
            std::vector<int16_t> cppArray(longArrayElements, longArrayElements + length);
            env->ReleaseLongArrayElements(value, longArrayElements, JNI_ABORT); // JNI_ABORT to avoid copying back changes
            cppMap[cKey] = cppArray;
        } else if (env->IsInstanceOf(javaValue, env->FindClass("[F"))) {
            // Handle byte array
            jfloatArray value = reinterpret_cast<jfloatArray>(javaValue);
            jsize length = env->GetArrayLength(value);
            jfloat *arrayElements = env->GetFloatArrayElements(value, nullptr);
            std::vector<float> cppArray(arrayElements, arrayElements + length);
            env->ReleaseFloatArrayElements(value, arrayElements, JNI_ABORT); // JNI_ABORT to avoid copying back changes
            cppMap[cKey] = cppArray;
        } else if (env->IsInstanceOf(javaValue, env->FindClass("[D"))) {
            // Handle byte array
            jdoubleArray value = reinterpret_cast<jdoubleArray>(javaValue);
            jsize length = env->GetArrayLength(value);
            jdouble *arrayElements = env->GetDoubleArrayElements(value, nullptr);
            std::vector<double> cppArray(arrayElements, arrayElements + length);
            env->ReleaseDoubleArrayElements(value, arrayElements, JNI_ABORT); // JNI_ABORT to avoid copying back changes
            cppMap[cKey] = cppArray;
        } else if (env->IsInstanceOf(javaValue, env->FindClass("[Z"))) {
            // Handle byte array
            jbooleanArray value = reinterpret_cast<jbooleanArray>(javaValue);
            jsize length = env->GetArrayLength(value);
            jboolean *arrayElements = env->GetBooleanArrayElements(value, nullptr);
            std::vector<bool> cppArray(arrayElements, arrayElements + length);
            env->ReleaseBooleanArrayElements(value, arrayElements, JNI_ABORT); // JNI_ABORT to avoid copying back changes
            cppMap[cKey] = cppArray;
        } if (env->IsInstanceOf(javaValue, env->FindClass("[Ljava/lang/String;"))) {
            // Handle array of strings
            jobjectArray stringArray = reinterpret_cast<jobjectArray>(javaValue);
            jsize arrayLength = env->GetArrayLength(stringArray);
            std::vector<std::string> cppStringArray;

            for (jsize i = 0; i < arrayLength; ++i) {
                jstring javaString = (jstring)env->GetObjectArrayElement(stringArray, i);
                const char *stringValue = env->GetStringUTFChars(javaString, nullptr);
                cppStringArray.emplace_back(stringValue);
                env->ReleaseStringUTFChars(javaString, stringValue);
                env->DeleteLocalRef(javaString);
            }

            cppMap[cKey] = cppStringArray;
        } else if (env->IsInstanceOf(javaValue, env->FindClass("[I"))) {
            // Handle int array
            jintArray value = reinterpret_cast<jintArray>(javaValue);
            jsize arrayLength = env->GetArrayLength(value);
            jint *intArrayElements = env->GetIntArrayElements(value, nullptr);
            std::vector<int> cppIntArray(intArrayElements, intArrayElements + arrayLength);
            env->ReleaseIntArrayElements(value, intArrayElements, JNI_ABORT); // JNI_ABORT to avoid copying back changes
            cppMap[cKey] = cppIntArray;
        }
        // Add similar blocks for handling other primitive arrays if needed

        env->ReleaseStringUTFChars(javaKey, cKey);
        env->DeleteLocalRef(javaKey);
        env->DeleteLocalRef(entry);
    }
//    if (model3DScene) {
//        model3DScene->sendCommands(cppMap);
//    }
    // Now cppMap contains the converted values from the Java Map
    // You can use cppMap as needed in your C++ code

    env->DeleteLocalRef(iterator);
    env->DeleteLocalRef(entrySet);
    env->DeleteLocalRef(commands);
}