#ifndef LEARNGLES_LIGHTCASTERSCENE_H
#define LEARNGLES_LIGHTCASTERSCENE_H

#include "Scene.h"

class LightCasterScene : public Scene {
public :
    LightCasterScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~LightCasterScene();
};

#endif //LEARNGLES_LIGHTCASTERSCENE_H
