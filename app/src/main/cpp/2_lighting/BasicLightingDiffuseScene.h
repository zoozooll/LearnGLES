//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_BASICLIGHTINGDIFFUSESCENE_H
#define LEARNGLES_BASICLIGHTINGDIFFUSESCENE_H

#include "Scene.h"
class BasicLightingDiffuseScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_BASICLIGHTINGDIFFUSESCENE_H
