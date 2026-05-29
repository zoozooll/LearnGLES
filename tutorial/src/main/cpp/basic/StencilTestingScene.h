#ifndef LEARNGLES_STENCILTESTINGSCENE_H
#define LEARNGLES_STENCILTESTINGSCENE_H

#include "TutorialScene.h"

class Shader;

class Camera;

class StencilTestingScene : public TutorialScene {
public :
    StencilTestingScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

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

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_STENCILTESTINGSCENE_H
