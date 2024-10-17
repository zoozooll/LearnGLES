//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_SCENEEXERCISE_H
#define LEARNGLES_SCENEEXERCISE_H

#include "BaseScene.h"
class SceneExercise : public BaseScene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_SCENEEXERCISE_H
