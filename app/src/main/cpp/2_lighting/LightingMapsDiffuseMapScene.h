//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_LIGHTINGMAPSDIFFUSEMAPSCENE_H
#define LEARNGLES_LIGHTINGMAPSDIFFUSEMAPSCENE_H

#include "Scene.h"
class LightingMapsDiffuseMapScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_LIGHTINGMAPSDIFFUSEMAPSCENE_H
