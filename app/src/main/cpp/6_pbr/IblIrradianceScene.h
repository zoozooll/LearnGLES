//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_IBLIRRADIANCESCENE_H
#define LEARNGLES_IBLIRRADIANCESCENE_H

#include "BaseScene.h"

class Shader;



class IblIrradianceScene : public BaseScene {
private:

    Shader* pbrShader = nullptr;
    Shader* equirectangularToCubemapShader = nullptr;
    Shader* irradianceShader = nullptr;
    Shader* backgroundShader = nullptr;

    unsigned int sphereVAO = 0;
    unsigned int cubeVAO = 0;
    unsigned int cubeVBO = 0;

    unsigned int envCubemap;
    unsigned int irradianceMap;
    // lights
// ------
    glm::vec3 lightPositions[4] = {
            glm::vec3(-10.0f,  10.0f, 10.0f),
            glm::vec3( 10.0f,  10.0f, 10.0f),
            glm::vec3(-10.0f, -10.0f, 10.0f),
            glm::vec3( 10.0f, -10.0f, 10.0f),
    };
    glm::vec3 lightColors[4] = {
            glm::vec3(300.0f, 300.0f, 300.0f),
            glm::vec3(300.0f, 300.0f, 300.0f),
            glm::vec3(300.0f, 300.0f, 300.0f),
            glm::vec3(300.0f, 300.0f, 300.0f)
    };
    int nrRows = 7;
    int nrColumns = 7;
    float spacing = 2.5;

    void renderSphere();
    void renderCube();
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_IBLIRRADIANCESCENE_H
