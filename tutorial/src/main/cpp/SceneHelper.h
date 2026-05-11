//
// Created by zoozo on 7/18/2023.
//

#ifndef LEARNGLES_SCENEHELPER_H
#define LEARNGLES_SCENEHELPER_H

#include "Scene.h"
#include <string>
#include <memory>
#include <cstring>

#include "basic/BasicGlesScene.h"


inline std::unique_ptr<Scene> GenSceneByName(const std::string& tutorial) {
    if (tutorial == "basic_gles") {
        return std::make_unique<BasicGlesScene>();
    }
    return nullptr;
}

#endif //LEARNGLES_SCENEHELPER_H
