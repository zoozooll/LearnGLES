#ifndef LEARNGLES_BASICLIGHTINGSCENE_H
#define LEARNGLES_BASICLIGHTINGSCENE_H

#include "Scene.h"

class BasicLightingScene : public Scene {
public :
    BasicLightingScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~BasicLightingScene();
};

#endif //LEARNGLES_BASICLIGHTINGSCENE_H
