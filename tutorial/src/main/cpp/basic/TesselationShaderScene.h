#ifndef LEARNGLES_TESSELATIONSHADERSCENE_H
#define LEARNGLES_TESSELATIONSHADERSCENE_H

#include "TutorialScene.h"

class Camera;

class Shader;

class TesselationShaderScene : public TutorialScene {
public :
    TesselationShaderScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~TesselationShaderScene();

private:
    Camera* m_camera = nullptr;
    Shader* tessHeightMapShader = nullptr;
    unsigned int terrainVAO = 0u, terrainVBO = 0u;
    unsigned int texture = 0u;
    unsigned int rez = 0u;

    int m_width = 0;
    int m_height = 0;

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_TESSELATIONSHADERSCENE_H
