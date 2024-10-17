//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_FRAMEBUFFERSMULTITEXTURESSCENE_H
#define LEARNGLES_FRAMEBUFFERSMULTITEXTURESSCENE_H

#include "BaseScene.h"

class Shader;


class FramebuffersMultiTexturesScene : public BaseScene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
private:
    Shader *shader = nullptr;
    Shader *screenShader = nullptr;

    unsigned int quadVAO, quadVBO;
    unsigned int framebuffer;
    unsigned int rbo;
    unsigned int textureColorbuffer0;
    unsigned int textureColorbuffer1;
    unsigned int textureColorbuffer2;
};


#endif //LEARNGLES_FRAMEBUFFERSMULTITEXTURESSCENE_H
