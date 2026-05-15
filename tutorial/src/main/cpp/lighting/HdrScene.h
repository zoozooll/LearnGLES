#ifndef LEARNGLES_HDRSCENE_H
#define LEARNGLES_HDRSCENE_H

#include "Scene.h"

class HdrScene : public Scene {
public :
    HdrScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~HdrScene();
};

#endif //LEARNGLES_HDRSCENE_H
