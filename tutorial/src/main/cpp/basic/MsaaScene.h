#ifndef LEARNGLES_MSAASCENE_H
#define LEARNGLES_MSAASCENE_H

#include "TutorialScene.h"

class Shader;
class Camera;

class MsaaScene : public TutorialScene {
public :
    MsaaScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~MsaaScene();

private:
    Camera* m_camera = nullptr;
    Shader* m_pShader = nullptr;
    unsigned int m_cubeVAO = 0u;
    unsigned int m_cubeVBO = 0u;

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_MSAASCENE_H
