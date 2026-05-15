#ifndef LEARNGLES_SSAOSCENE_H
#define LEARNGLES_SSAOSCENE_H

#include "Scene.h"

class SsaoScene : public Scene {
public :
    SsaoScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~SsaoScene();
};

#endif //LEARNGLES_SSAOSCENE_H
