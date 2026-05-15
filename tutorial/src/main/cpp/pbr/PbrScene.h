#ifndef LEARNGLES_PBRSCENE_H
#define LEARNGLES_PBRSCENE_H

#include "Scene.h"

class PbrScene : public Scene {
public :
    PbrScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~PbrScene();
};

#endif //LEARNGLES_PBRSCENE_H
