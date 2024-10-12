//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_BASICLIGHTINGDIFFUSESCENE_H
#define LEARNGLES_BASICLIGHTINGDIFFUSESCENE_H

#include "BaseScene.h"

class Shader;

class BasicLightingDiffuseScene : public BaseScene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;


private:
    Shader *lightingShader = nullptr;
    Shader *lightCubeShader = nullptr;
    unsigned int VBO, cubeVAO;
    unsigned int lightCubeVAO;
    glm::vec3 lightPos;
};


#endif //LEARNGLES_BASICLIGHTINGDIFFUSESCENE_H
