//
// Created by zoozo on 2026/5/25.
//

#include "JNITools.h"

//
// Created by aaron on 2021/11/19.
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

int JNITools::registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *jniMethods,
        int methodCount) {
    jclass classz = env->FindClass(className);
    if (classz == nullptr) {
        return JNI_FALSE;
    }
    if (env->RegisterNatives(classz, jniMethods, methodCount) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

void JNITools::unRegisterNativeMethods(JNIEnv *env, const char *className) {
    jclass classz = env->FindClass(className);
    if (classz == nullptr) {
        return;
    }
    env->UnregisterNatives(classz);
}

unsigned char *JNITools::jByteaArrayToChars(JNIEnv *env, jbyteArray bytearray) {
    if (bytearray == nullptr) {
        return nullptr;
    }
    jbyte *bytes = env->GetByteArrayElements(bytearray, 0);
    int chars_len = env->GetArrayLength(bytearray);
    auto *chars = static_cast<unsigned char *>(malloc(chars_len + 1 * sizeof(unsigned char)));
    memset(chars, 0, chars_len + 1);
    memcpy(chars, bytes, chars_len);
    chars[chars_len] = 0;

    env->ReleaseByteArrayElements(bytearray, bytes, 0);

    return chars;
}

unsigned char *JNITools::bitmapToPixelsData(JNIEnv *env, jobject &bitmap, int *size) {
    AndroidBitmapInfo info; // create a AndroidBitmapInfo
    int result;
    // 获取图片信息
    result = AndroidBitmap_getInfo(env, bitmap, &info);
    if (result != ANDROID_BITMAP_RESULT_SUCCESS) {
        return nullptr;
    }
    // 获取像素信息
    unsigned char *data;
    result = AndroidBitmap_lockPixels(env, bitmap, reinterpret_cast<void **>(&data));
    long sizsss = sizeof(data);
    if (result != ANDROID_BITMAP_RESULT_SUCCESS) {
        return nullptr;
    }
    size_t count = info.stride * info.height;
    unsigned char *resultData = (unsigned char *) malloc(count * sizeof(unsigned char));
    memcpy(resultData, data, count);

    // 像素信息不再使用后需要解除锁定
    result = AndroidBitmap_unlockPixels(env, bitmap);
    if (result != ANDROID_BITMAP_RESULT_SUCCESS) {
    }
    if (size != nullptr) {
        size[0] = info.width;
        size[1] = info.height;
    }
    return resultData;
}

jobject
JNITools::pixelsDataToBitmap(JNIEnv *jniEnv, const unsigned char *data, int width, int height) {
    jclass bitmapConfig = jniEnv->FindClass("android/graphics/Bitmap$Config");
    jfieldID rgba8888FieldID = jniEnv->GetStaticFieldID(bitmapConfig, "ARGB_8888",
            "Landroid/graphics/Bitmap$Config;");
    jobject rgba8888Obj = jniEnv->GetStaticObjectField(bitmapConfig, rgba8888FieldID);

    jclass bitmapClass = jniEnv->FindClass("android/graphics/Bitmap");
    jmethodID createBitmapMethodID = jniEnv->GetStaticMethodID(bitmapClass, "createBitmap",
            "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");
    jobject bitmapObj = jniEnv->CallStaticObjectMethod(bitmapClass, createBitmapMethodID, width,
            height, rgba8888Obj);

    jintArray pixels = jniEnv->NewIntArray(width * height);
    for (int i = 0; i < width * height; i++) {
        unsigned char red = data[i * 4];
        unsigned char green = data[i * 4 + 1];
        unsigned char blue = data[i * 4 + 2];
        unsigned char alpha = data[i * 4 + 3];
        int currentPixel = (alpha << 24) | (red << 16) | (green << 8) | (blue);
        jniEnv->SetIntArrayRegion(pixels, i, 1, &currentPixel);
    }
    jmethodID setPixelsMid = jniEnv->GetMethodID(bitmapClass, "setPixels", "([IIIIIII)V");
    jniEnv->CallVoidMethod(bitmapObj, setPixelsMid, pixels, 0, width, 0, 0, width, height);
    jniEnv->DeleteLocalRef(pixels);
    return bitmapObj;
}

template<class K>
std::map<K, std::any> JNITools::convertMapJava2Cpp(JNIEnv *env, const jobject &commands) {
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
    std::map<std::any, std::any> cppMap;

    while (env->CallBooleanMethod(iterator, hasNextMethod)) {
        jobject entry = env->CallObjectMethod(iterator, nextMethod);

        jclass entryClass = env->FindClass("java/util/Map$Entry");
        jmethodID getKeyMethod = env->GetMethodID(entryClass, "getKey", "()Ljava/lang/Object;");
        jmethodID getValueMethod = env->GetMethodID(entryClass, "getValue", "()Ljava/lang/Object;");

        jobject javaKey = env->CallObjectMethod(entry, getKeyMethod);
//        const char *cKey = env->GetStringUTFChars(javaKey, nullptr);
        auto cKey = convertJObject2Cpp<K>(env, javaKey);
        jobject javaValue = env->CallObjectMethod(entry, getValueMethod);

        cppMap[cKey] = convertJObject2Cpp<std::any>(env, javaValue);
        // Add similar blocks for handling other primitive arrays if needed

//        env->ReleaseStringUTFChars(javaKey, cKey);
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

template<class T>
T JNITools::convertJObject2Cpp(JNIEnv *env, jobject javaValue) {
    if (env->IsInstanceOf(javaValue, env->FindClass("java/lang/Byte"))) {
        jbyte value = env->CallByteMethod(javaValue, env->GetMethodID(env->FindClass("java/lang/Byte"), "byteValue", "()B"));
        return static_cast<char>(value);
    } else if (env->IsInstanceOf(javaValue, env->FindClass("java/lang/Short"))) {
        jshort value = env->CallShortMethod(javaValue, env->GetMethodID(env->FindClass("java/lang/Short"), "shortValue", "()S"));
        return static_cast<short>(value);
    } else if (env->IsInstanceOf(javaValue, env->FindClass("java/lang/Integer"))) {
        jint value = env->CallIntMethod(javaValue, env->GetMethodID(env->FindClass("java/lang/Integer"), "intValue", "()I"));
        return static_cast<int>(value);
    } else if (env->IsInstanceOf(javaValue, env->FindClass("java/lang/Long"))) {
        jlong value = env->CallLongMethod(javaValue, env->GetMethodID(env->FindClass("java/lang/Long"), "longValue", "()J"));
        return  static_cast<int64_t>(value);
    } else if (env->IsInstanceOf(javaValue, env->FindClass("java/lang/Float"))) {
        jfloat value = env->CallFloatMethod(javaValue, env->GetMethodID(env->FindClass("java/lang/Float"), "floatValue", "()F"));
        return static_cast<float>(value);
    } else if (env->IsInstanceOf(javaValue, env->FindClass("java/lang/Double"))) {
        jdouble value = env->CallDoubleMethod(javaValue, env->GetMethodID(env->FindClass("java/lang/Double"), "doubleValue", "()D"));
        return static_cast<double>(value);
    } else if (env->IsInstanceOf(javaValue, env->FindClass("java/lang/Boolean"))) {
        jboolean value = env->CallBooleanMethod(javaValue, env->GetMethodID(env->FindClass("java/lang/Boolean"), "booleanValue", "()Z"));
        return static_cast<bool>(value);
    } else if (env->IsInstanceOf(javaValue, env->FindClass("java/lang/String"))) {
        const char *stringValue = env->GetStringUTFChars((jstring)javaValue, nullptr);
        env->ReleaseStringUTFChars((jstring)javaValue, stringValue);
        return std::string(stringValue);
    } else if (env->IsInstanceOf(javaValue, env->FindClass("[B"))) {
        jbyteArray value = reinterpret_cast<jbyteArray>(javaValue);
        return convertJArray2Cpp(env, value);
    } else if (env->IsInstanceOf(javaValue, env->FindClass("[S"))) {
        jshortArray value = reinterpret_cast<jshortArray>(javaValue);
        return convertJArray2Cpp(env, value);
    } else if (env->IsInstanceOf(javaValue, env->FindClass("[J"))) {
        jlongArray value = reinterpret_cast<jlongArray>(javaValue);
        return convertJArray2Cpp(env, value);
    } else if (env->IsInstanceOf(javaValue, env->FindClass("[F"))) {
        jfloatArray value = reinterpret_cast<jfloatArray>(javaValue);
        return convertJArray2Cpp(env, value);
    } else if (env->IsInstanceOf(javaValue, env->FindClass("[D"))) {
        jdoubleArray value = reinterpret_cast<jdoubleArray>(javaValue);
        return convertJArray2Cpp(env, value);
    } else if (env->IsInstanceOf(javaValue, env->FindClass("[Z"))) {
        jbooleanArray value = reinterpret_cast<jbooleanArray>(javaValue);
        return convertJArray2Cpp(env, value);
    } if (env->IsInstanceOf(javaValue, env->FindClass("[Ljava/lang/String;"))) {
        jobjectArray stringArray = reinterpret_cast<jobjectArray>(javaValue);
        return convertJStringArray2Cpp(env, stringArray);
    } else if (env->IsInstanceOf(javaValue, env->FindClass("[I"))) {
        jintArray value = reinterpret_cast<jintArray>(javaValue);
        return convertJArray2Cpp(env, value);
    } else if (env->IsInstanceOf(javaValue, env->FindClass("java/util/Map"))) {

    }
    return {};
}

template<class T>
std::string JNITools::vectorToString(const std::vector<T>& myVector) {
    std::stringstream ss;
    for (const auto &element : myVector) {
        ss << element << ", ";
    }
    return ss.str();
}

template<typename K, typename V>
jobject JNITools::convertCppMapToJavaMap(JNIEnv* env, const std::map<K, V>& cppMap) {
    // Create a new java.util.HashMap<String, Object>
    jclass hashMapClass = env->FindClass("java/util/HashMap");
    jmethodID hashMapConstructor = env->GetMethodID(hashMapClass, "<init>", "()V");
    jobject javaMap = env->NewObject(hashMapClass, hashMapConstructor);

    // Get the put method from HashMap
    jmethodID putMethod = env->GetMethodID(hashMapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    // Iterate through cppMap and put key-value pairs into javaMap
    for (const auto& entry : cppMap) {
        const std::any& key = entry.first;
        const std::any& value = entry.second;

        // Convert key from C++ std::string to Java String
        jobject javaKey = convertCppToJavaObj(env, key);
        jobject javaValue = convertCppToJavaObj(env, value);
        if (javaKey && javaValue) {
            env->CallObjectMethod(javaMap, putMethod, javaKey, javaValue);
            // Release local references
            env->DeleteLocalRef(javaKey);
            env->DeleteLocalRef(javaValue);
        }
    }
    return javaMap;
}

jobjectArray
JNITools::convertCppStringArrayToJava(JNIEnv *env, const std::vector<std::string> &stringArray) {
    jobjectArray javaStringArray = env->NewObjectArray(static_cast<jsize>(stringArray.size()), env->FindClass("java/lang/String"), nullptr);
    for (size_t i = 0; i < stringArray.size(); ++i) {
        jstring javaString = env->NewStringUTF(stringArray[i].c_str());
        env->SetObjectArrayElement(javaStringArray, static_cast<jsize>(i), javaString);
        env->DeleteLocalRef(javaString);
    }
    return javaStringArray;
}

jlongArray
JNITools::convertCppLongArrayToJava(JNIEnv *env, const std::vector<long long int> &longLongArray) {
    jlongArray javaLongArray = env->NewLongArray(static_cast<jsize>(longLongArray.size()));
    env->SetLongArrayRegion(javaLongArray, 0, static_cast<jsize>(longLongArray.size()), reinterpret_cast<const jlong*>(longLongArray.data()));
    return javaLongArray;
}

jbooleanArray
JNITools::convertCppBoolArrayToJava(JNIEnv *env, const std::vector<bool> &boolArray) {
    jbooleanArray javaBoolArray = env->NewBooleanArray(static_cast<jsize>(boolArray.size()));
    // std::vector have no .data() because std::vector<bool> stores multiple values in 1 byte.
    jboolean data[boolArray.size()];
    for(unsigned int i = 0; i < boolArray.size(); i++) {
        data[i] = boolArray[i];
    }
    env->SetBooleanArrayRegion(javaBoolArray, 0, static_cast<jsize>(boolArray.size()), data);
    return javaBoolArray;
}

jdoubleArray
JNITools::convertCppDoubleArrayToJava(JNIEnv *env, const std::vector<double> &doubleArray) {
    jdoubleArray javaDoubleArray = env->NewDoubleArray(static_cast<jsize>(doubleArray.size()));
    env->SetDoubleArrayRegion(javaDoubleArray, 0, static_cast<jsize>(doubleArray.size()), reinterpret_cast<const jdouble*>(doubleArray.data()));
    return javaDoubleArray;
}

jfloatArray
JNITools::convertCppFloatArrayToJava(JNIEnv *env, const std::vector<float> &floatArray) {
    jfloatArray javaFloatArray = env->NewFloatArray(static_cast<jsize>(floatArray.size()));
    env->SetFloatArrayRegion(javaFloatArray, 0, static_cast<jsize>(floatArray.size()), reinterpret_cast<const jfloat*>(floatArray.data()));
    return javaFloatArray;
}

jintArray JNITools::convertCppIntArrayToJava(JNIEnv *env, const std::vector<int> &intArray) {
    jintArray javaIntArray = env->NewIntArray(static_cast<jsize>(intArray.size()));
    env->SetIntArrayRegion(javaIntArray, 0, static_cast<jsize>(intArray.size()), reinterpret_cast<const jint*>(intArray.data()));
    return javaIntArray;
}

jintArray
JNITools::convertCppUIntArrayToJava(JNIEnv *env, const std::vector<unsigned int> &uintArray) {
    jintArray javaIntArray = env->NewIntArray(static_cast<jsize>(uintArray.size()));
    env->SetIntArrayRegion(javaIntArray, 0, static_cast<jsize>(uintArray.size()), reinterpret_cast<const jint*>(uintArray.data()));
    return javaIntArray;
}

std::vector<char> JNITools::convertJArray2Cpp(JNIEnv *env, jbyteArray const &value) {
    jsize length = env->GetArrayLength(value);
    jbyte *byteArrayElements = env->GetByteArrayElements(value, nullptr);
    std::vector<char> cppByteArray(byteArrayElements, byteArrayElements + length);
    env->ReleaseByteArrayElements(value, byteArrayElements, JNI_ABORT); // JNI_ABORT to avoid copying back changes
    return cppByteArray;
}

std::vector<short> JNITools::convertJArray2Cpp(JNIEnv *env, jshortArray const &value) {
    jsize length = env->GetArrayLength(value);
    jshort *arrayElements = env->GetShortArrayElements(value, nullptr);
    std::vector<short> cppArray(arrayElements, arrayElements + length);
    env->ReleaseShortArrayElements(value, arrayElements, JNI_ABORT); // JNI_ABORT to avoid copying back changes
    return cppArray;
}

std::vector<int> JNITools::convertJArray2Cpp(JNIEnv *env, jintArray const &value) {
    jsize length = env->GetArrayLength(value);
    jint *arrayElements = env->GetIntArrayElements(value, nullptr);
    std::vector<int> cppArray(arrayElements, arrayElements + length);
    env->ReleaseIntArrayElements(value, arrayElements, JNI_ABORT); // JNI_ABORT to avoid copying back changes
    return cppArray;
}

std::vector<long long> JNITools::convertJArray2Cpp(JNIEnv *env, jlongArray const &value) {
    jsize length = env->GetArrayLength(value);
    jlong *arrayElements = env->GetLongArrayElements(value, nullptr);
    std::vector<long long> cppArray(arrayElements, arrayElements + length);
    env->ReleaseLongArrayElements(value, arrayElements, JNI_ABORT); // JNI_ABORT to avoid copying back changes
    return cppArray;
}

std::vector<float> JNITools::convertJArray2Cpp(JNIEnv *env, jfloatArray const &value) {
    jsize length = env->GetArrayLength(value);
    jfloat *arrayElements = env->GetFloatArrayElements(value, nullptr);
    std::vector<float> cppArray(arrayElements, arrayElements + length);
    env->ReleaseFloatArrayElements(value, arrayElements, JNI_ABORT); // JNI_ABORT to avoid copying back changes
    return cppArray;
}

std::vector<double> JNITools::convertJArray2Cpp(JNIEnv *env, jdoubleArray const &value) {
    jsize length = env->GetArrayLength(value);
    jdouble *arrayElements = env->GetDoubleArrayElements(value, nullptr);
    std::vector<double> cppArray(arrayElements, arrayElements + length);
    env->ReleaseDoubleArrayElements(value, arrayElements, JNI_ABORT); // JNI_ABORT to avoid copying back changes
    return cppArray;
}

std::vector<std::string> JNITools::convertJStringArray2Cpp(JNIEnv *env, jobjectArray const &value) {
    jsize arrayLength = env->GetArrayLength(value);
    std::vector<std::string> cppStringArray;

    for (jsize i = 0; i < arrayLength; ++i) {
        jstring javaString = (jstring)env->GetObjectArrayElement(value, i);
        const char *stringValue = env->GetStringUTFChars(javaString, nullptr);
        cppStringArray.emplace_back(stringValue);
        env->ReleaseStringUTFChars(javaString, stringValue);
        env->DeleteLocalRef(javaString);
    }
    return cppStringArray;
}

std::vector<bool> JNITools::convertJArray2Cpp(JNIEnv *env, jbooleanArray const &value) {
    jsize length = env->GetArrayLength(value);
    jboolean *arrayElements = env->GetBooleanArrayElements(value, nullptr);
    std::vector<bool> cppArray(arrayElements, arrayElements + length);
    env->ReleaseBooleanArrayElements(value, arrayElements, JNI_ABORT); // JNI_ABORT to avoid copying back changes
    return cppArray;
}

template<typename T>
jobject JNITools::convertCppToJavaObj(JNIEnv *env, const T &cppItem) {
    if (cppItem.type() == typeid(int)) {
        int intValue = std::any_cast<int>(cppItem);
        jobject javaValue = env->NewObject(env->FindClass("java/lang/Integer"), env->GetMethodID(env->FindClass("java/lang/Integer"), "<init>", "(I)V"), intValue);
        return javaValue;
    } else if(cppItem.type() == typeid(unsigned int)) {
        auto intValue = std::any_cast<unsigned int>(cppItem);
        jobject javaValue = env->NewObject(env->FindClass("java/lang/Integer"), env->GetMethodID(env->FindClass("java/lang/Integer"), "<init>", "(I)V"), (int)intValue);
        return javaValue;
    } else if (cppItem.type() == typeid(float)) {
        float floatValue = std::any_cast<float>(cppItem);
        jobject javaValue = env->NewObject(env->FindClass("java/lang/Float"), env->GetMethodID(env->FindClass("java/lang/Float"), "<init>", "(F)V"), floatValue);
        return javaValue;
    } else if (cppItem.type() == typeid(double)) {
        double doubleValue = std::any_cast<double>(cppItem);
        jobject javaValue = env->NewObject(env->FindClass("java/lang/Double"), env->GetMethodID(env->FindClass("java/lang/Double"), "<init>", "(D)V"), doubleValue);
        return javaValue;
    } else if (cppItem.type() == typeid(bool)) {
        bool boolValue = std::any_cast<bool>(cppItem);
        jobject javaValue = env->NewObject(env->FindClass("java/lang/Boolean"), env->GetMethodID(env->FindClass("java/lang/Boolean"), "<init>", "(Z)V"), boolValue);
        return javaValue;
    } else if (cppItem.type() == typeid(long long)) {
        long long longValue = std::any_cast<long long>(cppItem);
        jobject javaValue = env->NewObject(env->FindClass("java/lang/Long"), env->GetMethodID(env->FindClass("java/lang/Long"), "<init>", "(J)V"), longValue);
        return javaValue;
    } else if (cppItem.type() == typeid(std::string)) {
        std::string stringValue = std::any_cast<std::string>(cppItem);
        jstring javaValue = env->NewStringUTF(stringValue.c_str());
        return javaValue;
    } if (cppItem.type() == typeid(std::vector<int>)) {
        // Handle integer array
        std::vector<int> intArray = std::any_cast<std::vector<int>>(cppItem);
        jintArray javaValue = convertCppIntArrayToJava(env, intArray);
        return javaValue;
    } else if (cppItem.type() == typeid(std::vector<float>)) {
        // Handle float array
        std::vector<float> floatArray = std::any_cast<std::vector<float>>(cppItem);
        jfloatArray javaValue = convertCppFloatArrayToJava(env, floatArray);
        return javaValue;
    } else if (cppItem.type() == typeid(std::vector<double>)) {
        // Handle double array
        std::vector<double> doubleArray = std::any_cast<std::vector<double>>(cppItem);
        jdoubleArray javaValue = convertCppDoubleArrayToJava(env, doubleArray);
        return javaValue;
    } else if (cppItem.type() == typeid(std::vector<bool>)) {
        // Handle boolean array
        std::vector<bool> boolArray = std::any_cast<std::vector<bool>>(cppItem);
        jbooleanArray javaValue = convertCppBoolArrayToJava(env, boolArray);
        return javaValue;
    } else if (cppItem.type() == typeid(std::vector<long long>)) {
        // Handle long long array
        std::vector<long long> longLongArray = std::any_cast<std::vector<long long>>(cppItem);
        jlongArray javaValue = convertCppLongArrayToJava(env, longLongArray);
        return javaValue;
    } else if (cppItem.type() == typeid(std::vector<std::string>)) {
        // Handle string array
        std::vector<std::string> stringArray = std::any_cast<std::vector<std::string>>(cppItem);
        jobjectArray javaValue = convertCppStringArrayToJava(env, stringArray);
        return javaValue;
    } else if (cppItem.type() == typeid(std::map<unsigned int, float*>)) {
        // Handle string array
        auto local_value = std::any_cast<std::map<unsigned int, float*>>(cppItem);
        jobjectArray javaValue = convertCppMapToJavaMap(env, local_value);
        return javaValue;
    }
    return nullptr;
}

template<typename T>
jobject JNITools::convertCppVectorToJavaArray(JNIEnv* env, const std::vector<T> &myVector) {
    jlongArray javaLongArray = env->NewLongArray(static_cast<jsize>(myVector.size()));
    env->SetLongArrayRegion(javaLongArray, 0, static_cast<jsize>(myVector.size()), reinterpret_cast<const T*>(myVector.data()));

//    env->SetIntArrayRegion()
//    env->CallObjectMethod(javaMap, putMethod, javaKey, javaLongArray);
    return nullptr;
}
