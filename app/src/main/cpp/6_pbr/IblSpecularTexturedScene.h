//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_IBLSPECULARTEXTUREDSCENE_H
#define LEARNGLES_IBLSPECULARTEXTUREDSCENE_H

#include "BaseScene.h"



class Shader;

class IblSpecularTexturedScene : public BaseScene {
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
    unsigned int ironAlbedoMap;
    unsigned int ironNormalMap;
    unsigned int ironMetallicMap;
    unsigned int ironRoughnessMap;
    unsigned int ironAOMap;
    unsigned int goldAlbedoMap;
    unsigned int goldNormalMap;
    unsigned int goldMetallicMap;
    unsigned int goldRoughnessMap;
    unsigned int goldAOMap;
    unsigned int grassAlbedoMap;
    unsigned int grassNormalMap;
    unsigned int grassMetallicMap;
    unsigned int grassRoughnessMap;
    unsigned int grassAOMap;
    unsigned int plasticAlbedoMap;
    unsigned int plasticNormalMap;
    unsigned int plasticMetallicMap;
    unsigned int plasticRoughnessMap;
    unsigned int plasticAOMap;
    unsigned int wallAlbedoMap;
    unsigned int wallNormalMap;
    unsigned int wallMetallicMap;
    unsigned int wallRoughnessMap;
    unsigned int wallAOMap;
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

    void renderSphere();
    void renderCube();
    void renderQuad();
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_IBLSPECULARTEXTUREDSCENE_H
