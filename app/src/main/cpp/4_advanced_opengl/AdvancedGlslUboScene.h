//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_ADVANCEDGLSLUBOSCENE_H
#define LEARNGLES_ADVANCEDGLSLUBOSCENE_H

#include "Scene.h"
class AdvancedGlslUboScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_ADVANCEDGLSLUBOSCENE_H
