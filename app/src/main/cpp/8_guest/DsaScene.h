//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_DSASCENE_H
#define LEARNGLES_DSASCENE_H

#include "BaseScene.h"
class DsaScene : public BaseScene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_DSASCENE_H
