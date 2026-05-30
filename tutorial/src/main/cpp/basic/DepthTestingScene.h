//
// Created by zoozo on 2026/5/13.
//

#ifndef LEARNGLES_DEPTHTESTINGSCENE_H
#define LEARNGLES_DEPTHTESTINGSCENE_H

#include "TutorialScene.h"
#include <GLES3/gl32.h>

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

    bool isCullFace() const;

    void setCullFace(bool cullFace);

    bool isDepthTest() const;

    void setDepthTest(bool depthTest);

    bool isShowDepth() const;

    void setShowDepth(bool showDepth);

    GLenum getDepthFunc() const;

    void setDepthFunc(GLenum depthFunc);

private:
    Shader* m_pShader = nullptr;
    Shader* m_DepthShader = nullptr;
    Camera* m_camera = nullptr;
    unsigned int m_cubeVAO = 0u;
    unsigned int m_cubeVBO = 0u;
    unsigned int m_planeVAO = 0u;
    unsigned int m_planeVBO = 0u;
    unsigned int m_cubeTexture = 0u;
    unsigned int m_floorTexture = 0u;

    //Region Properties
    bool cullFace = true;
    bool depthTest = true;
    bool showDepth = false;
    GLenum depthFunc = GL_LESS;
    //EndRegion

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);

    void parseDepthtestEvent(std::map<std::string, std::any> &map);

    void parseDepthFuncEvent(std::map<std::string, std::any> &map);

    void parseCullFaceEvent(std::map<std::string, std::any> &map);
};


#endif //LEARNGLES_DEPTHTESTINGSCENE_H
