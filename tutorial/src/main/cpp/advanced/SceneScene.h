#ifndef LEARNGLES_SCENESCENE_H
#define LEARNGLES_SCENESCENE_H

#include "Scene.h"

class SceneScene : public Scene {
public :
    SceneScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~SceneScene();
};

#endif //LEARNGLES_SCENESCENE_H
