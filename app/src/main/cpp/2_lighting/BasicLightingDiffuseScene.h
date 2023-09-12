//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_BASICLIGHTINGDIFFUSESCENE_H
#define LEARNGLES_BASICLIGHTINGDIFFUSESCENE_H

#include "Scene.h"

class Camera;
class Shader;

class BasicLightingDiffuseScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
private:
    Shader *lightingShader = nullptr;
    Shader *lightCubeShader = nullptr;
    unsigned int SCR_WIDTH = 0;
    unsigned int SCR_HEIGHT = 0;
    unsigned int VBO, cubeVAO;
    unsigned int lightCubeVAO;
    glm::vec3 lightPos;
    Camera *camera = nullptr;
};


#endif //LEARNGLES_BASICLIGHTINGDIFFUSESCENE_H
