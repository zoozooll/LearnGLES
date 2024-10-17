 //
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_COMPUTESHADERHELLOWORLD_H
#define LEARNGLES_COMPUTESHADERHELLOWORLD_H

#include "BaseScene.h"
class ComputeshaderHelloworld : public BaseScene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy();
};


#endif //LEARNGLES_COMPUTESHADERHELLOWORLD_H
