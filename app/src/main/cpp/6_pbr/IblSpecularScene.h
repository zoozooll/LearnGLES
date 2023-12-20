//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_IBLSPECULARSCENE_H
#define LEARNGLES_IBLSPECULARSCENE_H

#include "Scene.h"
class IblSpecularScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_IBLSPECULARSCENE_H
