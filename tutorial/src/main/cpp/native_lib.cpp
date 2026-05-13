#include <jni.h>

#include <GLES3/gl32.h>
#include <android/asset_manager_jni.h>
#include <cstdlib>
#include <string>

#include "glerror.h"
#include "logutil.h"
#include "Scene.h"
#include "SceneHelper.h"
#include <memory>

//
// Created by Aaron Lee on 2023/07/12.
//
AAssetManager* mgr = nullptr;

std::string g_internalPath;

std::unique_ptr<Scene> g_scene;

extern "C"
JNIEXPORT void JNICALL
Java_com_minininja_learngles_NativeHelper_nativeOnInit(JNIEnv *env, jclass clazz, jstring tutorial) {
    LOGD(__FILE_NAME__, "OnInit");
    jboolean isCopy;
    auto tutorial_chars = env->GetStringUTFChars(tutorial, &isCopy);
    std::string tutorialTitle = std::string(tutorial_chars);
    g_scene = GenSceneByName(tutorialTitle);
    env->ReleaseStringUTFChars(tutorial, tutorial_chars);
    if (g_scene) {
        g_scene->init();
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_minininja_learngles_NativeHelper_nativeSizeChanged(JNIEnv *env, jclass clazz, jint width, jint height) {
    LOGD(__FILE_NAME__, "SizeChanged");
    if (g_scene) {
        g_scene->resize(width, height);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_minininja_learngles_NativeHelper_nativeDraw(JNIEnv *env, jclass clazz) {
    if (g_scene) {
        g_scene->draw();
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_minininja_learngles_NativeHelper_nativeDestroy(JNIEnv *env, jclass clazz) {
    LOGD(__FILE_NAME__, "nativeDestroy");
    if (g_scene) {
        g_scene->destroy();
        g_scene.release();
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_minininja_learngles_NativeHelper_setupNativeAsset(JNIEnv *env, jclass clazz, jobject am) {
    mgr = AAssetManager_fromJava(env, am);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_minininja_learngles_NativeHelper_setupInternalPath(JNIEnv *env, jclass clazz, jstring path) {
    jboolean is_copy;
    auto length = env->GetStringUTFLength(path);
    auto path_chars = env->GetStringUTFChars(path, &is_copy);
    g_internalPath = std::string(path_chars);
    env->ReleaseStringUTFChars(path, path_chars);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_minininja_learngles_NativeHelper_sendCommands(JNIEnv *env, jclass clazz, jobject commands) {

}