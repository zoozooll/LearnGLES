#ifndef LEARNGLES_PBRTEXTURESCENE_H
#define LEARNGLES_PBRTEXTURESCENE_H

#include "TutorialScene.h"

class Camera;

class PbrTextureScene : public TutorialScene {
public :
    PbrTextureScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~PbrTextureScene();

private:
    Camera* m_camera = nullptr;

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_PBRTEXTURESCENE_H
