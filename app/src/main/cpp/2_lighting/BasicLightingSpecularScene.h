//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_BASICLIGHTINGSPECULARSCENE_H
#define LEARNGLES_BASICLIGHTINGSPECULARSCENE_H

#include "BaseScene.h"

class Shader;

class BasicLightingSpecularScene : public BaseScene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

private:

    unsigned int VBO, cubeVAO;
    unsigned int lightCubeVAO;
    glm::vec3 lightPos;
    Shader *lightingShader = nullptr;
    Shader *lightCubeShader = nullptr;
};


#endif //LEARNGLES_BASICLIGHTINGSPECULARSCENE_H
