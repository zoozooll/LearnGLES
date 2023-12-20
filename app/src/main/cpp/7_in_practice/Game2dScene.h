//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_GAME2DSCENE_H
#define LEARNGLES_GAME2DSCENE_H

#include "Scene.h"
class Game2dScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_GAME2DSCENE_H
