//
// Created by zoozo on 7/25/2023.
//

#ifndef LEARNGLES_TRANSFORMATIONSSCENE_H
#define LEARNGLES_TRANSFORMATIONSSCENE_H

#include "Scene.h"

class Shader;

class TransformationsScene : public Scene {
public:
    void init() override;

    void resize(int i, int i1) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_TRANSFORMATIONSSCENE_H
