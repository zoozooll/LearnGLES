#ifndef LEARNGLES_INSTANCESCENE_H
#define LEARNGLES_INSTANCESCENE_H

#include "TutorialScene.h"

class Shader;
class Camera;

class InstanceScene : public TutorialScene {
public :
    InstanceScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~InstanceScene();

private:
    Camera* m_camera = nullptr;
    Shader* m_pShader = nullptr;
    unsigned int m_quadVAO = 0u;
    unsigned int m_quadVBO = 0u;
    unsigned int m_instanceVBO = 0u;

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_INSTANCESCENE_H
