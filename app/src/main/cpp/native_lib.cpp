#include <jni.h>

#include <GLES3/gl32.h>

#include "glerror.h"

//
// Created by Aaron Lee on 2023/07/12.
//


extern "C"
JNIEXPORT void JNICALL
Java_com_example_learngles_NativeLibHelper_nativeSurfaceCreate(JNIEnv *env, jclass clazz) {

}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_learngles_NativeLibHelper_nativeSurfaceChanged(JNIEnv *env, jclass clazz,
                                                                jint width, jint height) {
    // TODO: implement nativeSurfaceChanged()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_learngles_NativeLibHelper_nativeDraw(JNIEnv *env, jclass clazz) {
    // TODO: implement nativeDraw()
}