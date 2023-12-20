//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_SSAOSCENE_H
#define LEARNGLES_SSAOSCENE_H

#include "Scene.h"
class SsaoScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_SSAOSCENE_H
