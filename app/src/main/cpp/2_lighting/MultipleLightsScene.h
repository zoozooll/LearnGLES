//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_MULTIPLELIGHTSSCENE_H
#define LEARNGLES_MULTIPLELIGHTSSCENE_H

#include "BaseScene.h"
#include "SceneTouchEvent.h"


class Shader;

class MultipleLightsScene : public BaseScene{
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
    unsigned int diffuseMap = 0U;
    unsigned int specularMap = 0u;
    glm::vec3 cubePositions[10] {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glm::vec3 pointLightPositions[4] = {
            glm::vec3( 0.7f,  0.2f,  2.0f),
            glm::vec3( 2.3f, -3.3f, -4.0f),
            glm::vec3(-4.0f,  2.0f, -12.0f),
            glm::vec3( 0.0f,  0.0f, -3.0f)
    };
};


#endif //LEARNGLES_MULTIPLELIGHTSSCENE_H
