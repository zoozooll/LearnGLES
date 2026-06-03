#ifndef LEARNGLES_SHADOWSCENE_H
#define LEARNGLES_SHADOWSCENE_H

#include "TutorialScene.h"

class Camera;
class Shader;

class ShadowScene : public TutorialScene {
public :
    ShadowScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~ShadowScene();

private:
    Camera* m_camera = nullptr;

    Shader* m_pShader = nullptr;
    Shader* m_pSimpleDepthShader = nullptr;
    Shader* m_pDebugDepthQuad = nullptr;

    unsigned int m_cubeVAO = 0u;
    unsigned int m_cubeVBO = 0u;
    unsigned int m_planeVAO = 0u;
    unsigned int m_planeVBO = 0u;
    unsigned int m_quadVAO = 0u;
    unsigned int m_quadVBO = 0u;

    unsigned int m_woodTexture = 0u;
    unsigned int m_depthMapFBO = 0u;
    unsigned int m_depthMap = 0u;

    int m_width = 0;
    int m_height = 0;

    void renderQuad();
    void renderCube();
    void renderScene(const Shader &shader);

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_SHADOWSCENE_H
