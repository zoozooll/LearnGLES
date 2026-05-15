#ifndef LEARNGLES_AREALIGHTSSCENE_H
#define LEARNGLES_AREALIGHTSSCENE_H

#include "Scene.h"

class AreaLightsScene : public Scene {
public :
    AreaLightsScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~AreaLightsScene();
};

#endif //LEARNGLES_AREALIGHTSSCENE_H
