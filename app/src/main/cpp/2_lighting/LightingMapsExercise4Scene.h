

//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_LIGHTINGMAPSEXERCISE4SCENE_H
#define LEARNGLES_LIGHTINGMAPSEXERCISE4SCENE_H

#include "Scene.h"
class LightingMapsExercise4Scene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_LIGHTINGMAPSEXERCISE4SCENE_H
