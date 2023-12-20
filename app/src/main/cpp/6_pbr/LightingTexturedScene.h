//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_LIGHTINGTEXTUREDSCENE_H
#define LEARNGLES_LIGHTINGTEXTUREDSCENE_H

#include "Scene.h"
class LightingTexturedScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_LIGHTINGTEXTUREDSCENE_H
