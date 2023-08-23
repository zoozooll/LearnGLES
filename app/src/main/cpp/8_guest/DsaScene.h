//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_DSASCENE_H
#define LEARNGLES_DSASCENE_H

#include "Scene.h"
class DsaScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_DSASCENE_H
