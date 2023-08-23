//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_LIGHTINGSCENE_H
#define LEARNGLES_LIGHTINGSCENE_H

#include "Scene.h"
class LightingScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_LIGHTINGSCENE_H
