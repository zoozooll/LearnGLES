//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_LIGHTINGTEXTUREDSCENE_H
#define LEARNGLES_LIGHTINGTEXTUREDSCENE_H

#include "Scene.h"

class Camera;

class Shader;

class LightingTexturedScene : public Scene {
private:
    Camera *camera = nullptr;
    Shader *shader = nullptr;

    unsigned int sphereVAO = 0u;
    unsigned int albedo;
    unsigned int normal;
    unsigned int metallic;
    unsigned int roughness;
    unsigned int ao;

    glm::vec3 lightPositions[1] = {
            glm::vec3(0.0f, 0.0f, 10.0f),
    };
    glm::vec3 lightColors[1] = {
            glm::vec3(150.0f, 150.0f, 150.0f),
    };
    int nrRows = 7;
    int nrColumns = 7;
    float spacing = 2.5;

    void renderSphere();

public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_LIGHTINGTEXTUREDSCENE_H
