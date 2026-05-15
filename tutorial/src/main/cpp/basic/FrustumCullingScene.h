#ifndef LEARNGLES_FRUSTUMCULLINGSCENE_H
#define LEARNGLES_FRUSTUMCULLINGSCENE_H

#include "Scene.h"

class FrustumCullingScene : public Scene {
public :
    FrustumCullingScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~FrustumCullingScene();
};

#endif //LEARNGLES_FRUSTUMCULLINGSCENE_H
