//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_ADVANCEDGLSLUBOSCENE_H
#define LEARNGLES_ADVANCEDGLSLUBOSCENE_H

#include "BaseScene.h"

class Shader;
class AdvancedGlslUboScene : public BaseScene {
private:
    Shader *shaderRed = nullptr;
    Shader *shaderGreen = nullptr;
    Shader *shaderBlue = nullptr;
    Shader *shaderYellow = nullptr;

    // cube VAO
    unsigned int cubeVAO = 0u, cubeVBO = 0u;
    unsigned int uboMatrices = 0u;

public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_ADVANCEDGLSLUBOSCENE_H
