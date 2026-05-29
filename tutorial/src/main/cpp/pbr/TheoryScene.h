#ifndef LEARNGLES_THEORYSCENE_H
#define LEARNGLES_THEORYSCENE_H

#include "TutorialScene.h"

class Camera;

class TheoryScene : public TutorialScene {
public :
    TheoryScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~TheoryScene();

private:
    Camera* m_camera = nullptr;

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_THEORYSCENE_H
