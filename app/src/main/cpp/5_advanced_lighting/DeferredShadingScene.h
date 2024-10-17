//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_DEFERREDSHADINGSCENE_H
#define LEARNGLES_DEFERREDSHADINGSCENE_H

#include "BaseScene.h"

#include <vector>
#include <glm/glm.hpp>

class Shader;
class Model;

class DeferredShadingScene : public BaseScene {
private:

    Shader* shaderGeometryPass = nullptr;
    Shader* shaderLightingPass = nullptr;
    Shader* shaderLightBox = nullptr;
    Model* backpack = nullptr;

    unsigned int gBuffer;
    unsigned int gPosition, gNormal, gAlbedoSpec;
    unsigned int rboDepth;
    unsigned int quadVAO;
    unsigned int quadVBO;
    unsigned int cubeVAO;
    unsigned int cubeVBO;

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


#endif //LEARNGLES_DEFERREDSHADINGSCENE_H
