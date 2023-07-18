//
// Created by zoozo on 7/18/2023.
//

#ifndef LEARNGLES_SCENEHELPER_H
#define LEARNGLES_SCENEHELPER_H

#include "Scene.h"
#include <cstring>

#include "getting_started/HelloWindowScene.h"
#include "getting_started/HelloWindowClearScene.h"
#include "getting_started/HelloTriangleScene.h"

inline Scene* GenSceneByName(const char *tutorial) {
    if (!strcmp(tutorial, "hello_window")) {
        return new HelloWindowScene;
    } else if (!strcmp(tutorial, "hello_window_clear")) {
        return new HelloWindowClearScene;
    } else if (!strcmp(tutorial, "hello_triangle")) {
        return new HelloTriangleScene;
    } else if (!strcmp(tutorial, "hello_triangle_indexed")) {

    } else if (!strcmp(tutorial, "hello_triangle_exercise1")) {

    } else if (!strcmp(tutorial, "hello_triangle_exercise2")) {

    } else if (!strcmp(tutorial, "hello_triangle_exercise3")) {

    } else if (!strcmp(tutorial, "shaders_uniform")) {

    } else if (!strcmp(tutorial, "shaders_interpolation")) {

    } else if (!strcmp(tutorial, "shaders_class")) {

    } else if (!strcmp(tutorial, "shaders_exercise1")) {

    } else if (!strcmp(tutorial, "shaders_exercise2")) {

    } else if (!strcmp(tutorial, "shaders_exercise3")) {

    } else if (!strcmp(tutorial, "textures")) {

    } else if (!strcmp(tutorial, "texture_combined")) {

    } else if (!strcmp(tutorial, "texture_exercise1")) {

    } else if (!strcmp(tutorial, "texture_exercise2")) {

    } else if (!strcmp(tutorial, "texture_exercise3")) {

    } else if (!strcmp(tutorial, "texture_exercise4")) {

    } else if (!strcmp(tutorial, "transformations")) {

    } else if (!strcmp(tutorial, "transformations_exercise1")) {

    } else if (!strcmp(tutorial, "transformations_exercise2")) {

    } else if (!strcmp(tutorial, "coordinate_systems")) {

    } else if (!strcmp(tutorial, "coordinate_systems_depth")) {

    } else if (!strcmp(tutorial, "coordinate_systems_multiple")) {

    } else if (!strcmp(tutorial, "coordinate_systems_exercise")) {

    } else if (!strcmp(tutorial, "camera_circle")) {

    } else if (!strcmp(tutorial, "camera_keyboard_dt")) {

    } else if (!strcmp(tutorial, "camera_mouse_zoom")) {

    } else if (!strcmp(tutorial, "camera_class")) {

    } else if (!strcmp(tutorial, "camera_exercise1")) {

    } else if (!strcmp(tutorial, "camera_exercise2")) {

    }
    return nullptr;
}

#endif //LEARNGLES_SCENEHELPER_H
