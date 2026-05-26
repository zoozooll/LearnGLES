//
// Created by Aaron Lee on 2026/5/25.
//

#ifndef LEARNGLES_JNITOOLS_H
#define LEARNGLES_JNITOOLS_H

#include <jni.h>
#include <map>
#include <any>

class JNITools {
public:
    // 用于动态注册JNI函数
    static int registerNativeMethods(JNIEnv *, const char *, JNINativeMethod *, int);

    // 用于注销动态注册的JNI函数
    static void unRegisterNativeMethods(JNIEnv *, const char *);

    static unsigned char *bitmapToPixelsData(JNIEnv *env, jobject &bitmap, int *size);

    static unsigned char *jByteaArrayToChars(JNIEnv *env, jbyteArray bytearray);

    static jobject pixelsDataToBitmap(JNIEnv *env,const unsigned char *data, int width, int height);

    template<class K>
    static std::map<K, std::any> convertMapJava2Cpp(JNIEnv *env, const jobject &commands);

    template<class T>
    static T convertJObject2Cpp(JNIEnv *env, jobject javaValue);

    template<typename K, typename V>
    static jobject convertCppMapToJavaMap(JNIEnv* env, const std::map<K, V>& cppMap);

    template<class T> static
    std::string vectorToString(const std::vector<T>& myVector);

    template<class T> static
    jobject convertCppVectorToJavaArray(JNIEnv* env, const std::vector<T>& myVector);

    static jintArray convertCppIntArrayToJava(JNIEnv *env, const std::vector<int> &intArray);

    static jintArray convertCppUIntArrayToJava(JNIEnv *env, const std::vector<unsigned int> &intArray);

    static jfloatArray
    convertCppFloatArrayToJava(JNIEnv *env, const std::vector<float> &floatArray);

    static jdoubleArray
    convertCppDoubleArrayToJava(JNIEnv *env, const std::vector<double> &doubleArray);

    static jbooleanArray convertCppBoolArrayToJava(JNIEnv *env, const std::vector<bool> &boolArray);

    static jlongArray
    convertCppLongArrayToJava(JNIEnv *env, const std::vector<long long int> &longLongArray);

    template<typename T> static jobject
    convertCppToJavaObj(JNIEnv *env, const T &cppItem);

    static jobjectArray
    convertCppStringArrayToJava(JNIEnv *env, const std::vector<std::string> &stringArray);

    static std::vector<char> convertJArray2Cpp(JNIEnv *env, jbyteArray const &value);

    static std::vector<short> convertJArray2Cpp(JNIEnv *env, jshortArray const &value);

    static std::vector<int> convertJArray2Cpp(JNIEnv *env, jintArray const &value);

    static std::vector<long long> convertJArray2Cpp(JNIEnv *env, jlongArray const &value);

    static std::vector<float> convertJArray2Cpp(JNIEnv *env, jfloatArray const &value);

    static std::vector<double> convertJArray2Cpp(JNIEnv *env, jdoubleArray const &value);

    static std::vector<bool> convertJArray2Cpp(JNIEnv *env, jbooleanArray const &value);

    static std::vector<std::string> convertJStringArray2Cpp(JNIEnv *env, jobjectArray const &value);
};


#endif //LEARNGLES_JNITOOLS_H
