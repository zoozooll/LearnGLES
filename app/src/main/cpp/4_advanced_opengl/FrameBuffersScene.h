//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_FRAMEBUFFERSSCENE_H
#define LEARNGLES_FRAMEBUFFERSSCENE_H

#include "BaseScene.h"
#include "SceneTouchEvent.h"


class Shader;

class FrameBuffersScene : public BaseScene{
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
    unsigned int framebuffer;
    unsigned int rbo;
    unsigned int cubeTexture;
    unsigned int floorTexture;
    unsigned int textureColorbuffer;
};


#endif //LEARNGLES_FRAMEBUFFERSSCENE_H
