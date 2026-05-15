//
// Created by zoozo on 2026/5/13.
//

#ifndef LEARNGLES_DEPTHTESTINGSCENE_H
#define LEARNGLES_DEPTHTESTINGSCENE_H

#include "Scene.h"

class Shader;

class Camera;

class DepthTestingScene : public Scene {
public :
    DepthTestingScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~DepthTestingScene();

private:
    Shader* m_pShader = nullptr;
    Camera* m_camera = nullptr;
    unsigned int m_cubeVAO = 0u;
    unsigned int m_cubeVBO = 0u;
    unsigned int m_planeVAO = 0u;
    unsigned int m_planeVBO = 0u;
    unsigned int m_cubeTexture = 0u;
    unsigned int m_floorTexture = 0u;
};


#endif //LEARNGLES_DEPTHTESTINGSCENE_H
