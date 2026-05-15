#ifndef LEARNGLES_STENCILTESTINGSCENE_H
#define LEARNGLES_STENCILTESTINGSCENE_H

#include "Scene.h"

class Shader;

class Camera;

class StencilTestingScene : public Scene {
public :
    StencilTestingScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~StencilTestingScene();

private:
    Camera* m_camera = nullptr;
    Shader* m_pShader = nullptr;
    Shader* m_pShaderSingleColor = nullptr;
    unsigned int m_cubeVAO = 0u;
    unsigned int m_cubeVBO = 0u;
    unsigned int m_planeVAO = 0u;
    unsigned int m_planeVBO = 0u;
    unsigned int m_cubeTexture = 0u;
    unsigned int m_floorTexture = 0u;
};

#endif //LEARNGLES_STENCILTESTINGSCENE_H
