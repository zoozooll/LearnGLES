#ifndef LEARNGLES_BLOOMSCENE_H
#define LEARNGLES_BLOOMSCENE_H

#include "Scene.h"

class BloomScene : public Scene {
public :
    BloomScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~BloomScene();
};

#endif //LEARNGLES_BLOOMSCENE_H
