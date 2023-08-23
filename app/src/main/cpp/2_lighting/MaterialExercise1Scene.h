//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_MATERIALEXERCISE1SCENE_H
#define LEARNGLES_MATERIALEXERCISE1SCENE_H

#include "Scene.h"
class MaterialExercise1Scene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_MATERIALEXERCISE1SCENE_H
