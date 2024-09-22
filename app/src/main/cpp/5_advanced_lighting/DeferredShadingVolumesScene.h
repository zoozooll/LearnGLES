//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_DEFERREDSHADINGVOLUMESSCENE_H
#define LEARNGLES_DEFERREDSHADINGVOLUMESSCENE_H

#include <vector>
#include <glm/glm.hpp>

#include "Scene.h"

class Camera;

class Shader;

class Model;

class DeferredShadingVolumesScene : public Scene {
private:
    unsigned int quadVAO;
    unsigned int quadVBO;
    unsigned int cubeVAO;
    unsigned int cubeVBO;

    unsigned int gBuffer;
    unsigned int gPosition, gNormal, gAlbedoSpec;
    unsigned int rboDepth;

    int SCR_WIDTH = 0;
    int SCR_HEIGHT = 0;

    Camera *camera = nullptr;
    Shader *shaderGeometryPass = nullptr;
    Shader *shaderLightingPass = nullptr;
    Shader *shaderLightBox = nullptr;
    Model *backpack = nullptr;

    std::vector<glm::vec3> objectPositions;
    const unsigned int NR_LIGHTS = 32;
    std::vector<glm::vec3> lightPositions;
    std::vector<glm::vec3> lightColors;

    void renderQuad();
    void renderCube();
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_DEFERREDSHADINGVOLUMESSCENE_H
