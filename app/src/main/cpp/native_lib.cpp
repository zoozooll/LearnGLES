#include <jni.h>

#include <GLES3/gl32.h>
#include <android/asset_manager_jni.h>
#include <cstdlib>

#include "glerror.h"
#include "SceneHelper.h"
#include "Scene.h"

//
// Created by Aaron Lee on 2023/07/12.
//
AAssetManager* mgr = nullptr;

char *g_internalPath = nullptr;

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
extern "C"
JNIEXPORT void JNICALL
Java_com_example_learngles_NativeLibHelper_setupInternalPath(JNIEnv *env, jclass clazz,
                                                             jstring path) {
    jboolean is_copy;
    auto length = env->GetStringUTFLength(path);
    auto path_chars = env->GetStringUTFChars(path, &is_copy);
    g_internalPath = static_cast<char *>(malloc(length + 1));
    memcpy(g_internalPath, path_chars, length + 1);
    env->ReleaseStringUTFChars(path, path_chars);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_mouselee_object3ddemo2_Renderer_onSingleTouch(JNIEnv *, jobject , jfloat x,
                                                       jfloat y) {
//    LOGI("TRANSFORM", "onSingleTouch (%f, %f)", x, y);
    glm::vec2 director(x, y);
    if (m_ModelObject)
        m_ModelObject->yawPitch(director);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_mouselee_object3ddemo2_Renderer_onZooming(JNIEnv *, jobject , jfloat start_distance,
                                                   jfloat end_distance) {
    if (m_ModelObject && start_distance != 0.f && end_distance != 0.f) {
        auto scale = end_distance / start_distance;
        m_ModelObject->scale(scale);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_mouselee_object3ddemo2_Renderer_onMoving(JNIEnv *, jobject , jfloat start_center_x,
                                                  jfloat start_center_y, jfloat end_center_x,
                                                  jfloat end_center_y) {
    LOGI("TRANSFORM", "onMoving (%f, %f) --> (%f, %f)", start_center_x, start_center_y, end_center_x, end_center_y);
    if (m_ModelObject) {
        glm::vec2 start_center(start_center_x, -start_center_y);
        glm::vec2 end_center(end_center_x, -end_center_y);
        m_ModelObject->move(start_center, end_center);
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_mouselee_object3ddemo2_Renderer_onTwoFingersRotating(JNIEnv *env, jobject thiz,
    jfloat angle) {
    LOGI("TRANSFORM", "onTwoFingersRotating %f", angle);
    if (m_ModelObject)
        m_ModelObject->roll(angle);

}
