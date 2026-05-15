#ifndef LEARNGLES_DSASCENE_H
#define LEARNGLES_DSASCENE_H

#include "Scene.h"

class DsaScene : public Scene {
public :
    DsaScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~DsaScene();
};

#endif //LEARNGLES_DSASCENE_H
