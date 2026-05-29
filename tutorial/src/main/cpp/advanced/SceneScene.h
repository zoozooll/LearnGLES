#ifndef LEARNGLES_SCENESCENE_H
#define LEARNGLES_SCENESCENE_H

#include "TutorialScene.h"

class Camera;

class SceneScene : public TutorialScene {
public :
    SceneScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~SceneScene();

private:
    Camera* camera = nullptr;

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_SCENESCENE_H
