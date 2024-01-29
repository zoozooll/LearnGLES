//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_FRAMEBUFFERSMULTITEXTURESSCENE_H
#define LEARNGLES_FRAMEBUFFERSMULTITEXTURESSCENE_H

#include "Scene.h"

class Shader;
class Camera;

class FramebuffersMultiTexturesScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
private:
    unsigned int SCR_WIDTH = 0, SCR_HEIGHT = 0;

    Shader *shader = nullptr;
    Shader *screenShader = nullptr;
    Camera *camera = nullptr;
    unsigned int quadVAO, quadVBO;
    unsigned int framebuffer;
    unsigned int rbo;
    unsigned int textureColorbuffer0;
    unsigned int textureColorbuffer1;
    unsigned int textureColorbuffer2;
};


#endif //LEARNGLES_FRAMEBUFFERSMULTITEXTURESSCENE_H
