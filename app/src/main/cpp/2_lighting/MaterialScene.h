//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_MATERIALSCENE_H
#define LEARNGLES_MATERIALSCENE_H

#include "BaseScene.h"
#include "Camera.h"
class Shader;

class MaterialScene : public BaseScene{
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
private:
    unsigned int VBO, cubeVAO;
    unsigned int lightCubeVAO;
    Shader *lightingShader = nullptr;
    Shader *lightCubeShader = nullptr;

    glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
};


#endif //LEARNGLES_MATERIALSCENE_H
