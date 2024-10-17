//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_FRAMEBUFFERSEXERCISE1SCENE_H
#define LEARNGLES_FRAMEBUFFERSEXERCISE1SCENE_H

#include "BaseScene.h"

#include "SceneTouchEvent.h"

class Shader;


class FramebuffersExercise1Scene : public BaseScene{
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

private:
    Shader *shader = nullptr;
    Shader *screenShader = nullptr;

    unsigned int cubeVAO, cubeVBO;
    unsigned int planeVAO, planeVBO;
    unsigned int quadVAO, quadVBO;
    unsigned int cubeTexture;
    unsigned int floorTexture;
    unsigned int framebuffer;
    unsigned int rbo;
    unsigned int textureColorbuffer;
};


#endif //LEARNGLES_FRAMEBUFFERSEXERCISE1SCENE_H
