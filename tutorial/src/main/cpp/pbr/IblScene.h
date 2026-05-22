#ifndef LEARNGLES_IBLSCENE_H
#define LEARNGLES_IBLSCENE_H

#include "Scene.h"

class Camera;
class Shader;

class IblScene : public Scene {
public :
    IblScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~IblScene();

private:
    Camera* camera = nullptr;
    Shader* pbrShader = nullptr;
    Shader* equirectangularToCubemapShader = nullptr;
    Shader* irradianceShader = nullptr;
    Shader* prefilterShader = nullptr;
    Shader* brdfShader = nullptr;
    Shader* backgroundShader = nullptr;

    unsigned int sphereVAO = 0u;
    unsigned int indexCount = 0u;

    unsigned int cubeVAO = 0u;
    unsigned int cubeVBO = 0u;

    unsigned int quadVAO = 0u;
    unsigned int quadVBO = 0u;

    unsigned int captureFBO = 0u;
    unsigned int captureRBO = 0u;
    unsigned int hdrTexture = 0u;
    unsigned int envCubemap = 0u;
    unsigned int irradianceMap = 0u;
    unsigned int prefilterMap = 0u;
    unsigned int brdfLUTTexture = 0u;

    // PBR textures
    unsigned int ironAlbedoMap = 0u, ironNormalMap = 0u, ironMetallicMap = 0u, ironRoughnessMap = 0u, ironAOMap = 0u;
    unsigned int goldAlbedoMap = 0u, goldNormalMap = 0u, goldMetallicMap = 0u, goldRoughnessMap = 0u, goldAOMap = 0u;
    unsigned int grassAlbedoMap = 0u, grassNormalMap = 0u, grassMetallicMap = 0u, grassRoughnessMap = 0u, grassAOMap = 0u;
    unsigned int plasticAlbedoMap = 0u, plasticNormalMap = 0u, plasticMetallicMap = 0u, plasticRoughnessMap = 0u, plasticAOMap = 0u;
    unsigned int wallAlbedoMap = 0u, wallNormalMap = 0u, wallMetallicMap = 0u, wallRoughnessMap = 0u, wallAOMap = 0u;

    glm::vec3 lightPositions[4];
    glm::vec3 lightColors[4];

    int m_width = 0;
    int m_height = 0;

    void renderSphere();
    void renderCube();
    void renderQuad();
};

#endif //LEARNGLES_IBLSCENE_H
