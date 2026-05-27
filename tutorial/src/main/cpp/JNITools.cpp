//
// Created by Aaron Lee on 2021/11/19.
//

#include "JNITools.h"

#include <android/bitmap.h>
#include <malloc.h>
#include <cstring>
#include <string>
#include <vector>
#include <typeinfo>

#include "logutil.h"
#include <sstream>

std::map<std::string, std::any> converMapJava2Cpp(JNIEnv *env, jobject commands) {
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
        } else if (env->IsInstanceOf(javaValue, env->FindClass("java/util/Map"))) {
//            LOGINFO("convertMapJava2Cpp value is map");
            jobject entrySet_inner = env->CallObjectMethod(javaValue, entrySetMethod);
            jobject iterator_inner = env->CallObjectMethod(entrySet_inner, iteratorMethod);
            std::map<unsigned int, std::vector<float>> cppMap_inner;
            while (env->CallBooleanMethod(iterator_inner, hasNextMethod)) {
                jobject entry_inner = env->CallObjectMethod(iterator_inner, nextMethod);
                jobject javaKey_inner = env->CallObjectMethod(entry_inner, getKeyMethod);
                jobject javaValue_inner = env->CallObjectMethod(entry_inner, getValueMethod);
                if (env->IsInstanceOf(javaKey_inner, env->FindClass("java/lang/Integer"))
                        && env->IsInstanceOf(javaValue_inner, env->FindClass("[F"))) {
                    jint key_inner = env->CallIntMethod(javaKey_inner, env->GetMethodID(env->FindClass("java/lang/Integer"), "intValue", "()I"));
                    jfloatArray value_inner = reinterpret_cast<jfloatArray>(javaValue_inner);
                    jsize length = env->GetArrayLength(value_inner);
                    jfloat *arrayElements = env->GetFloatArrayElements(value_inner, nullptr);
                    std::vector<float> cppArray(arrayElements, arrayElements + length);
                    env->ReleaseFloatArrayElements(value_inner, arrayElements, JNI_ABORT);

//                    LOGINFO("convertMapJava2Cpp value is map [%d] :  %s", key_inner, vectorToString(cppArray).c_str());
                    cppMap_inner[(unsigned int) key_inner] = cppArray;
                }
            }
            cppMap[cKey] = cppMap_inner;
        }
        // Add similar blocks for handling other primitive arrays if needed

        env->ReleaseStringUTFChars(javaKey, cKey);
        env->DeleteLocalRef(javaKey);
        env->DeleteLocalRef(entry);
    }
    // Now cppMap contains the converted values from the Java Map
    // You can use cppMap as needed in your C++ code

    env->DeleteLocalRef(iterator);
    env->DeleteLocalRef(entrySet);
    env->DeleteLocalRef(commands);
    return cppMap;
}


jobject convertCppMapToJavaMap(JNIEnv* env, const std::map<std::string, std::any> &cppMap) {
    // Create a new java.util.HashMap<String, Object>
    jclass hashMapClass = env->FindClass("java/util/HashMap");
    jmethodID hashMapConstructor = env->GetMethodID(hashMapClass, "<init>", "()V");
    jobject javaMap = env->NewObject(hashMapClass, hashMapConstructor);

    // Get the put method from HashMap
    jmethodID putMethod = env->GetMethodID(hashMapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    // Iterate through cppMap and put key-value pairs into javaMap
    for (const auto& entry : cppMap) {
        const std::string& key = entry.first;
        const std::any& value = entry.second;

        // Convert key from C++ std::string to Java String
        jstring javaKey = env->NewStringUTF(key.c_str());

        // Check if the value is an array
        if (value.type() == typeid(int)) {
            int intValue = std::any_cast<int>(value);
            jobject javaValue = env->NewObject(env->FindClass("java/lang/Integer"), env->GetMethodID(env->FindClass("java/lang/Integer"), "<init>", "(I)V"), intValue);
            env->CallObjectMethod(javaMap, putMethod, javaKey, javaValue);
        } else if(value.type() == typeid(unsigned int)) {
            auto intValue = std::any_cast<unsigned int>(value);
            jobject javaValue = env->NewObject(env->FindClass("java/lang/Integer"), env->GetMethodID(env->FindClass("java/lang/Integer"), "<init>", "(I)V"), (int)intValue);
            env->CallObjectMethod(javaMap, putMethod, javaKey, javaValue);
        } else if (value.type() == typeid(float)) {
            float floatValue = std::any_cast<float>(value);
            jobject javaValue = env->NewObject(env->FindClass("java/lang/Float"), env->GetMethodID(env->FindClass("java/lang/Float"), "<init>", "(F)V"), floatValue);
            env->CallObjectMethod(javaMap, putMethod, javaKey, javaValue);
        } else if (value.type() == typeid(double)) {
            double doubleValue = std::any_cast<double>(value);
            jobject javaValue = env->NewObject(env->FindClass("java/lang/Double"), env->GetMethodID(env->FindClass("java/lang/Double"), "<init>", "(D)V"), doubleValue);
            env->CallObjectMethod(javaMap, putMethod, javaKey, javaValue);
        } else if (value.type() == typeid(bool)) {
            bool boolValue = std::any_cast<bool>(value);
            jobject javaValue = env->NewObject(env->FindClass("java/lang/Boolean"), env->GetMethodID(env->FindClass("java/lang/Boolean"), "<init>", "(Z)V"), boolValue);
            env->CallObjectMethod(javaMap, putMethod, javaKey, javaValue);
        } else if (value.type() == typeid(long long)) {
            long long longValue = std::any_cast<long long>(value);
            jobject javaValue = env->NewObject(env->FindClass("java/lang/Long"), env->GetMethodID(env->FindClass("java/lang/Long"), "<init>", "(J)V"), longValue);
            env->CallObjectMethod(javaMap, putMethod, javaKey, javaValue);
        } else if (value.type() == typeid(std::string)) {
            std::string stringValue = std::any_cast<std::string>(value);
            jstring javaValue = env->NewStringUTF(stringValue.c_str());
            env->CallObjectMethod(javaMap, putMethod, javaKey, javaValue);
        } if (value.type() == typeid(std::vector<int>)) {
            // Handle integer array
            std::vector<int> intArray = std::any_cast<std::vector<int>>(value);
            jintArray javaIntArray = env->NewIntArray(static_cast<jsize>(intArray.size()));
            env->SetIntArrayRegion(javaIntArray, 0, static_cast<jsize>(intArray.size()), reinterpret_cast<const jint*>(intArray.data()));
            env->CallObjectMethod(javaMap, putMethod, javaKey, javaIntArray);
        } else if (value.type() == typeid(std::vector<float>)) {
            // Handle float array
            std::vector<float> floatArray = std::any_cast<std::vector<float>>(value);
            jfloatArray javaFloatArray = env->NewFloatArray(static_cast<jsize>(floatArray.size()));
            env->SetFloatArrayRegion(javaFloatArray, 0, static_cast<jsize>(floatArray.size()), reinterpret_cast<const jfloat*>(floatArray.data()));
            env->CallObjectMethod(javaMap, putMethod, javaKey, javaFloatArray);
        } else if (value.type() == typeid(std::vector<double>)) {
            // Handle double array
            std::vector<double> doubleArray = std::any_cast<std::vector<double>>(value);
            jdoubleArray javaDoubleArray = env->NewDoubleArray(static_cast<jsize>(doubleArray.size()));
            env->SetDoubleArrayRegion(javaDoubleArray, 0, static_cast<jsize>(doubleArray.size()), reinterpret_cast<const jdouble*>(doubleArray.data()));
            env->CallObjectMethod(javaMap, putMethod, javaKey, javaDoubleArray);
        } else if (value.type() == typeid(std::vector<bool>)) {
            // Handle boolean array
            std::vector<bool> boolArray = std::any_cast<std::vector<bool>>(value);
            jbooleanArray javaBoolArray = env->NewBooleanArray(static_cast<jsize>(boolArray.size()));
            // std::vector have no .data() because std::vector<bool> stores multiple values in 1 byte.
            jboolean data[boolArray.size()];
            for(unsigned int i = 0; i < boolArray.size(); i++) {
                data[i] = boolArray[i];
            }
            env->SetBooleanArrayRegion(javaBoolArray, 0, static_cast<jsize>(boolArray.size()), data);
            env->CallObjectMethod(javaMap, putMethod, javaKey, javaBoolArray);
        } else if (value.type() == typeid(std::vector<long long>)) {
            // Handle long long array
            std::vector<long long> longLongArray = std::any_cast<std::vector<long long>>(value);
            jlongArray javaLongArray = env->NewLongArray(static_cast<jsize>(longLongArray.size()));
            env->SetLongArrayRegion(javaLongArray, 0, static_cast<jsize>(longLongArray.size()), reinterpret_cast<const jlong*>(longLongArray.data()));
            env->CallObjectMethod(javaMap, putMethod, javaKey, javaLongArray);
        } else if (value.type() == typeid(std::vector<std::string>)) {
            // Handle string array
            std::vector<std::string> stringArray = std::any_cast<std::vector<std::string>>(value);
            jobjectArray javaStringArray = env->NewObjectArray(static_cast<jsize>(stringArray.size()), env->FindClass("java/lang/String"), nullptr);
            for (size_t i = 0; i < stringArray.size(); ++i) {
                jstring javaString = env->NewStringUTF(stringArray[i].c_str());
                env->SetObjectArrayElement(javaStringArray, static_cast<jsize>(i), javaString);
                env->DeleteLocalRef(javaString);
            }
            env->CallObjectMethod(javaMap, putMethod, javaKey, javaStringArray);
        }
            // Add similar blocks for handling other array types if needed
        else {
            // Handle unsupported types or throw an exception
        }

        // Release local references
        env->DeleteLocalRef(javaKey);
    }

    return javaMap;
}