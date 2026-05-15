#ifndef LEARNGLES_THEORYSCENE_H
#define LEARNGLES_THEORYSCENE_H

#include "Scene.h"

class TheoryScene : public Scene {
public :
    TheoryScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~TheoryScene();
};

#endif //LEARNGLES_THEORYSCENE_H
