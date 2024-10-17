//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_COLORSCENE_H
#define LEARNGLES_COLORSCENE_H

#include "BaseScene.h"

class Shader;

class ColorScene : public BaseScene  {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

private:
    unsigned int VBO = 0, cubeVAO = 0;
    Shader *lightingShader = nullptr;
    Shader *lightCubeShader = nullptr;
    unsigned int lightCubeVAO = 0;
    glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
};


#endif //LEARNGLES_COLORSCENE_H
