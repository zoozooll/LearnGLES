#ifndef LEARNGLES_SHADOWSCENE_H
#define LEARNGLES_SHADOWSCENE_H

#include "Scene.h"

class ShadowScene : public Scene {
public :
    ShadowScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~ShadowScene();
};

#endif //LEARNGLES_SHADOWSCENE_H
