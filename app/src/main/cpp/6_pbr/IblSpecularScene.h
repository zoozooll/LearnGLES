//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_IBLSPECULARSCENE_H
#define LEARNGLES_IBLSPECULARSCENE_H

#include "BaseScene.h"



class Shader;

class IblSpecularScene : public BaseScene {
private:


    Shader* pbrShader = nullptr;
    Shader* equirectangularToCubemapShader = nullptr;
    Shader* irradianceShader = nullptr;
    Shader* prefilterShader = nullptr;
    Shader* brdfShader = nullptr;
    Shader* backgroundShader = nullptr;

    unsigned int cubeVAO = 0;
    unsigned int cubeVBO = 0;
    unsigned int quadVAO = 0;
    unsigned int quadVBO = 0;
    unsigned int sphereVAO = 0;
    unsigned int irradianceMap;
    unsigned int prefilterMap;
    unsigned int brdfLUTTexture;
    unsigned int envCubemap;
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
    void renderQuad();
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_IBLSPECULARSCENE_H
