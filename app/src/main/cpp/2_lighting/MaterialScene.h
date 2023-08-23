//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_MATERIALSCENE_H
#define LEARNGLES_MATERIALSCENE_H

#include "Scene.h"
class MaterialScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_MATERIALSCENE_H
