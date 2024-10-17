

//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_LIGHTINGMAPSEXERCISE4SCENE_H
#define LEARNGLES_LIGHTINGMAPSEXERCISE4SCENE_H

#include "BaseScene.h"
#include "SceneTouchEvent.h"


class Shader;

class LightingMapsExercise4Scene : public BaseScene  {
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

#endif //LEARNGLES_LIGHTINGMAPSEXERCISE4SCENE_H
