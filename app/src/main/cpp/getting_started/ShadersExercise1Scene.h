//
// Created by zoozo on 7/19/2023.
//

#ifndef LEARNGLES_SHADERSEXERCISE1SCENE_H
#define LEARNGLES_SHADERSEXERCISE1SCENE_H

#include "Scene.h"

class ShadersExercise1Scene : public Scene {
public:
    void init() override;

    void resize(int i, int i1) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_SHADERSEXERCISE1SCENE_H
