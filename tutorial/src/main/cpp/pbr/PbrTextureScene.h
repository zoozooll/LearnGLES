#ifndef LEARNGLES_PBRTEXTURESCENE_H
#define LEARNGLES_PBRTEXTURESCENE_H

#include "TutorialScene.h"

class PbrTextureScene : public TutorialScene {
public :
    PbrTextureScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~PbrTextureScene();
};

#endif //LEARNGLES_PBRTEXTURESCENE_H
