#ifndef LEARNGLES_SCENESCENE_H
#define LEARNGLES_SCENESCENE_H

#include "TutorialScene.h"

class SceneScene : public TutorialScene {
public :
    SceneScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~SceneScene();
};

#endif //LEARNGLES_SCENESCENE_H
