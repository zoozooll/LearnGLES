#include <jni.h>

#include <GLES3/gl32.h>
#include <android/asset_manager_jni.h>
#include <cstdlib>

#include "glerror.h"
#include "SceneHelper.h"
#include "BaseScene.h"
#include "SceneTouchEvent.h"
#include "logutil.h"

//
// Created by Aaron Lee on 2023/07/12.
//
AAssetManager* mgr = nullptr;

char *g_internalPath = nullptr;

Scene *g_scene = nullptr;

extern "C"
JNIEXPORT void JNICALL
Java_com_example_learngles_NativeLibHelper_nativeSurfaceCreate(JNIEnv *env, jclass clazz,
                                                               jstring tutorial) {
    LOGD(__FILE_NAME__, "SurfaceCreate");
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

    LOGD(__FILE_NAME__, "SurfaceChanged");
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
    LOGD(__FILE_NAME__, "nativeDestroy");
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
Java_com_example_learngles_NativeLibHelper_onSingleTouch(JNIEnv *env, jclass clazz, jfloat x,
                                                         jfloat y) {
    if (g_scene) {
        auto baseTouchEvent = dynamic_cast<SceneTouchEvent*>(g_scene);
        if (baseTouchEvent) {
            baseTouchEvent->yawPitch(glm::vec2(x,y));
        }
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_learngles_NativeLibHelper_onZooming(JNIEnv *env, jclass clazz,
                                                     jfloat prev_distance, jfloat distance) {
    if (g_scene && prev_distance != 0.f and distance != 0.f) {
        auto baseTouchEvent = dynamic_cast<SceneTouchEvent*>(g_scene);
        if (baseTouchEvent) {
            baseTouchEvent->scale(distance / prev_distance);
        }
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_learngles_NativeLibHelper_onTwoFingersRotating(JNIEnv *env, jclass clazz,
                                                                jfloat angle) {
    if (g_scene) {
        auto baseTouchEvent = dynamic_cast<SceneTouchEvent*>(g_scene);
        if (baseTouchEvent) {
            baseTouchEvent->roll(angle);
        }
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_learngles_NativeLibHelper_onMoving(JNIEnv *env, jclass clazz, jfloat x, jfloat y,
                                                    jfloat x1, jfloat y1) {
    if (g_scene) {
        auto baseTouchEvent = dynamic_cast<SceneTouchEvent*>(g_scene);
        if (baseTouchEvent) {
            baseTouchEvent->move({x, y}, {x1, y1});
        }
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_learngles_NativeLibHelper_onSingleClick(JNIEnv *env, jclass clazz, jfloat x,
                                                         jfloat y) {
    if (g_scene) {
        auto baseTouchEvent = dynamic_cast<SceneTouchEvent*>(g_scene);
        if (baseTouchEvent) {
            baseTouchEvent->onSingleClick({x, y});
        }
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_learngles_NativeLibHelper_onDoubleClick(JNIEnv *env, jclass clazz, jfloat x,
                                                         jfloat y) {
    if (g_scene) {
        auto baseTouchEvent = dynamic_cast<SceneTouchEvent*>(g_scene);
        if (baseTouchEvent) {
            baseTouchEvent->onDoubleClick({x, y});
        }
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_learngles_NativeLibHelper_onLongPress(JNIEnv *env, jclass clazz, jfloat x,
                                                       jfloat y) {
    if (g_scene) {
        auto baseTouchEvent = dynamic_cast<SceneTouchEvent*>(g_scene);
        if (baseTouchEvent) {
            baseTouchEvent->onLongPress({x, y});
        }
    }
}
