//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_LIGHTINGCASTERSSPOTSCENE_H
#define LEARNGLES_LIGHTINGCASTERSSPOTSCENE_H

#include "Scene.h"
class LightingCastersSpotScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_LIGHTINGCASTERSSPOTSCENE_H
