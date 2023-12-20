//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_MATERIALEXERCISE1SCENE_H
#define LEARNGLES_MATERIALEXERCISE1SCENE_H

#include "Scene.h"

#include "Scene.h"
#include "Camera.h"
class Shader;
class MaterialExercise1Scene : public Scene {
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
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    unsigned int SCR_WIDTH = 0;
    unsigned int SCR_HEIGHT = 0;
};


#endif //LEARNGLES_MATERIALEXERCISE1SCENE_H
