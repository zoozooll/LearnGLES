//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_SKELETALANIMATIONSCENE_H
#define LEARNGLES_SKELETALANIMATIONSCENE_H

#include "BaseScene.h"

class Camera;
class Shader;
class AnimatedModel;
class Animator;

class SkeletalAnimationScene : public BaseScene {
private:
    Camera *camera = nullptr;
    Shader *ourShader = nullptr;
    AnimatedModel *ourModel = nullptr;
    Animator *animator = nullptr;

    float deltaTime = 0.F;
    float lastFrame = 0.F;

    int SCR_WIDTH = 0;
    int SCR_HEIGHT = 0;

public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_SKELETALANIMATIONSCENE_H
