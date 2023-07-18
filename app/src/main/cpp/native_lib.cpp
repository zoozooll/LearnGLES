#include <jni.h>

#include <GLES3/gl32.h>
#include <android/asset_manager_jni.h>

#include "glerror.h"
#include "SceneHelper.h"
#include "Scene.h"

//
// Created by Aaron Lee on 2023/07/12.
//
AAssetManager* mgr = nullptr;

static Scene *g_scene = nullptr;

extern "C"
JNIEXPORT void JNICALL
Java_com_example_learngles_NativeLibHelper_nativeSurfaceCreate(JNIEnv *env, jclass clazz,
                                                               jstring tutorial) {
    jboolean isCopy;
    auto tutorial_chars = env->GetStringUTFChars(tutorial, &isCopy);
    g_scene = GenSceneByName(tutorial_chars);
    env->ReleaseStringUTFChars(tutorial, tutorial_chars);
    if (g_scene) {
        g_scene->init();
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_learngles_NativeLibHelper_nativeSurfaceChanged(JNIEnv *env, jclass clazz,
                                                                jint width, jint height) {
    if (g_scene) {
        g_scene->resize(width, height);
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_learngles_NativeLibHelper_nativeDraw(JNIEnv *env, jclass clazz) {
    if (g_scene) {
        g_scene->draw();
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_learngles_NativeLibHelper_nativeDestroy(JNIEnv *env, jclass clazz) {
    if (g_scene) {
        g_scene->destroy();
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_learngles_NativeLibHelper_setupNativeAsset(JNIEnv *env, jclass clazz, jobject am) {
    mgr = AAssetManager_fromJava(env, am);
}