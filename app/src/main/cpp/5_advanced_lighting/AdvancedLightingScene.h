//
// Created by Aaron Lee on 2023/08/07.
//

#ifndef LEARNGLES_ADVANCEDLIGHTINGSCENE_H
#define LEARNGLES_ADVANCEDLIGHTINGSCENE_H

#include <glm/glm.hpp>

#include "Scene.h"
#include "Camera.h"

class Shader;

class AdvancedLightingScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

private:
    Shader *shader = nullptr;
    unsigned int planeVAO = 0;
    unsigned int planeVBO = 0;
    unsigned int floorTexture = 0;
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
};


#endif //LEARNGLES_ADVANCEDLIGHTINGSCENE_H
