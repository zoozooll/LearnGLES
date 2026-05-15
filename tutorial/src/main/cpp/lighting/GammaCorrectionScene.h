#ifndef LEARNGLES_GAMMACORRECTIONSCENE_H
#define LEARNGLES_GAMMACORRECTIONSCENE_H

#include "Scene.h"

class GammaCorrectionScene : public Scene {
public :
    GammaCorrectionScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~GammaCorrectionScene();
};

#endif //LEARNGLES_GAMMACORRECTIONSCENE_H
