//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_IBLSPECULARTEXTUREDSCENE_H
#define LEARNGLES_IBLSPECULARTEXTUREDSCENE_H

#include "Scene.h"
class IblSpecularTexturedScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_IBLSPECULARTEXTUREDSCENE_H
