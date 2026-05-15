#ifndef LEARNGLES_CUBEMAPSCENE_H
#define LEARNGLES_CUBEMAPSCENE_H

#include "Scene.h"

#include <vector>
#include <string>

class Shader;
class Camera;

class CubemapScene : public Scene {
public :
    CubemapScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~CubemapScene();

private:
    Camera* m_camera = nullptr;
    Shader* m_pShader = nullptr;
    Shader* m_pSkyboxShader = nullptr;

    unsigned int m_cubeVAO = 0u;
    unsigned int m_cubeVBO = 0u;
    unsigned int m_skyboxVAO = 0u;
    unsigned int m_skyboxVBO = 0u;

    unsigned int m_cubeTexture = 0u;
    unsigned int m_cubemapTexture = 0u;
};

#endif //LEARNGLES_CUBEMAPSCENE_H
