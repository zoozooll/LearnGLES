//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_OITSCENE_H
#define LEARNGLES_OITSCENE_H

#include "BaseScene.h"
class OitScene : public BaseScene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_OITSCENE_H
