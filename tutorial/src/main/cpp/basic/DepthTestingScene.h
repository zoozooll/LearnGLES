//
// Created by zoozo on 2026/5/13.
//

#ifndef LEARNGLES_DEPTHTESTINGSCENE_H
#define LEARNGLES_DEPTHTESTINGSCENE_H

#include "TutorialScene.h"

class Shader;

class Camera;

class DepthTestingScene : public TutorialScene {
public :
    DepthTestingScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

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

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};


#endif //LEARNGLES_DEPTHTESTINGSCENE_H
