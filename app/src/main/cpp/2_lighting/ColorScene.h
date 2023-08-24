//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_COLORSCENE_H
#define LEARNGLES_COLORSCENE_H

#include "Scene.h"

class Camera;
class Shader;

class ColorScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

private:
    unsigned int VBO = 0, cubeVAO = 0;
    Camera *camera = nullptr;
    Shader *lightingShader = nullptr;
    Shader *lightCubeShader = nullptr;
    unsigned int lightCubeVAO = 0;
    glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
};


#endif //LEARNGLES_COLORSCENE_H
