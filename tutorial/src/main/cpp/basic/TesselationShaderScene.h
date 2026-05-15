#ifndef LEARNGLES_TESSELATIONSHADERSCENE_H
#define LEARNGLES_TESSELATIONSHADERSCENE_H

#include "Scene.h"

class TesselationShaderScene : public Scene {
public :
    TesselationShaderScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~TesselationShaderScene();
};

#endif //LEARNGLES_TESSELATIONSHADERSCENE_H
