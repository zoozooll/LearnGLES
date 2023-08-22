//
// Created by zoozo on 7/18/2023.
//

#ifndef LEARNGLES_SCENEHELPER_H
#define LEARNGLES_SCENEHELPER_H

#include "Scene.h"
#include <cstring>

#include "1_getting_started/HelloWindowScene.h"
#include "1_getting_started/HelloWindowClearScene.h"
#include "1_getting_started/HelloTriangleScene.h"
#include "1_getting_started/HelloTriangleIndexedScene.h"
#include "1_getting_started/HelloTriangleExercise1Scene.h"
#include "1_getting_started/HelloTriangleExercise2Scene.h"
#include "1_getting_started/HelloTriangleExercise3Scene.h"
#include "1_getting_started/ShadersUniformScene.h"
#include "1_getting_started/ShadersInterpolationScene.h"
#include "1_getting_started/ShadersClassScene.h"
#include "1_getting_started/ShadersExercise1Scene.h"
#include "1_getting_started/ShadersExercise2Scene.h"
#include "1_getting_started/ShadersExercise3Scene.h"
#include "1_getting_started/TexturesScene.h"
#include "1_getting_started/TextureCombinedScene.h"
#include "1_getting_started/TransformationsScene.h"
#include "1_getting_started/TextureExercise1Scene.h"
#include "1_getting_started/TextureExercise2Scene.h"
#include "1_getting_started/TextureExercise3Scene.h"
#include "1_getting_started/TextureExercise4Scene.h"
#include "1_getting_started/TransformationsExercise1Scene.h"
#include "1_getting_started/TransformationsExercise2Scene.h"
#include "1_getting_started/CoordinateSystemScene.h"
#include "1_getting_started/CoordinateSystemDepthScene.h"
#include "1_getting_started/CoordinateSystemMultipleScene.h"
#include "1_getting_started/CoordinateSystemExercise3Scene.h"
#include "1_getting_started/CameraScene.h"G
#include "3_model_loading/ModelLoadingScene.h"
#include "5_advanced_lighting/AdvancedLightingScene.h"

inline Scene* GenSceneByName(const char *tutorial) {
    if (!strcmp(tutorial, "hello_window")) {
        return new HelloWindowScene;
    } else if (!strcmp(tutorial, "hello_window_clear")) {
        return new HelloWindowClearScene;
    } else if (!strcmp(tutorial, "hello_triangle")) {
        return new HelloTriangleScene;
    } else if (!strcmp(tutorial, "hello_triangle_indexed")) {
        return new HelloTriangleIndexedScene;
    } else if (!strcmp(tutorial, "hello_triangle_exercise1")) {
        return new HelloTriangleExercise1Scene;
    } else if (!strcmp(tutorial, "hello_triangle_exercise2")) {
        return new HelloTriangleExercise2Scene;
    } else if (!strcmp(tutorial, "hello_triangle_exercise3")) {
        return new HelloTriangleExercise3Scene;
    } else if (!strcmp(tutorial, "shaders_uniform")) {
        return new ShadersUniformScene;
    } else if (!strcmp(tutorial, "shaders_interpolation")) {
        return new ShadersInterpolationScene;
    } else if (!strcmp(tutorial, "shaders_class")) {
        return new ShadersClassScene;
    } else if (!strcmp(tutorial, "shaders_exercise1")) {
        return new ShadersExercise1Scene;
    } else if (!strcmp(tutorial, "shaders_exercise2")) {
         return new ShadersExercise2Scene;
    } else if (!strcmp(tutorial, "shaders_exercise3")) {
         return new ShadersExercise3Scene;
    } else if (!strcmp(tutorial, "textures")) {
        return new TexturesScene;
    } else if (!strcmp(tutorial, "texture_combined")) {
        return new TextureCombinedScene;
    } else if (!strcmp(tutorial, "transformations")) {
        return new TransformationsScene;
    } else if (!strcmp(tutorial, "texture_exercise1")) {
        return new TextureExercise1Scene;
    } else if (!strcmp(tutorial, "texture_exercise2")) {
        return new TextureExercise2Scene;
    } else if (!strcmp(tutorial, "texture_exercise3")) {
        return new TextureExercise3Scene;
    } else if (!strcmp(tutorial, "texture_exercise4")) {
        return new TextureExercise4Scene;
    } else if (!strcmp(tutorial, "transformations_exercise1")) {
        return new TransformationsExercise1Scene;
    } else if (!strcmp(tutorial, "transformations_exercise2")) {
        return new TransformationsExercise2Scene;
    } else if (!strcmp(tutorial, "coordinate_systems")) {
        return new CoordinateSystemScene;
    } else if (!strcmp(tutorial, "coordinate_systems_depth")) {
        return new CoordinateSystemDepthScene;
    } else if (!strcmp(tutorial, "coordinate_systems_multiple")) {
        return new CoordinateSystemMultipleScene;
    } else if (!strcmp(tutorial, "coordinate_systems_exercise")) {
//        return new CoordinateSystemExercise3Scene;
    } else if (!strcmp(tutorial, "camera_circle")) {

    } else if (!strcmp(tutorial, "camera_keyboard_dt")) {

    } else if (!strcmp(tutorial, "camera_mouse_zoom")) {

    } else if (!strcmp(tutorial, "camera_class")) {
        return new CameraScene;
    } else if (!strcmp(tutorial, "camera_exercise1")) {

    } else if (!strcmp(tutorial, "camera_exercise2")) {

    } else if (!strcmp(tutorial, "model_loading")) {
        return new ModelLoadingScene;
    } else if (!strcmp(tutorial, "advanced_lighting")) {
        return new AdvancedLightingScene;
    }
    return nullptr;
}

#endif //LEARNGLES_SCENEHELPER_H
