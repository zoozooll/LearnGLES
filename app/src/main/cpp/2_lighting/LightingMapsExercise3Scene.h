//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_LIGHTINGMAPSEXERCISE3_H
#define LEARNGLES_LIGHTINGMAPSEXERCISE3_H

#include "BaseScene.h"
#include "SceneTouchEvent.h"


class Shader;

class LightingMapsExercise3Scene : public BaseScene  {
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
    unsigned int diffuseMap;
};


#endif //LEARNGLES_LIGHTINGMAPSEXERCISE3_H
