//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_LIGHTINGMAPSSPECULARMAPSCENE_H
#define LEARNGLES_LIGHTINGMAPSSPECULARMAPSCENE_H

#include "Scene.h"
class LightingMapsSpecularMapScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_LIGHTINGMAPSSPECULARMAPSCENE_H
