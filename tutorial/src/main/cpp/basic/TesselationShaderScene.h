#ifndef LEARNGLES_TESSELATIONSHADERSCENE_H
#define LEARNGLES_TESSELATIONSHADERSCENE_H

#include "Scene.h"

class Camera;

class Shader;

class TesselationShaderScene : public Scene {
public :
    TesselationShaderScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~TesselationShaderScene();

private:
    Camera* m_camera = nullptr;
    Shader* tessHeightMapShader = nullptr;
    unsigned int terrainVAO = 0u, terrainVBO = 0u;
    unsigned int texture = 0u;
    unsigned int rez = 0u;

    int m_width = 0;
    int m_height = 0;
};

#endif //LEARNGLES_TESSELATIONSHADERSCENE_H
