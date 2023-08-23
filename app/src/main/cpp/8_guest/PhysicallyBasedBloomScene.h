//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_PHYSICALLYBASEDBLOOMSCENE_H
#define LEARNGLES_PHYSICALLYBASEDBLOOMSCENE_H

#include "Scene.h"
class PhysicallyBasedBloomScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_PHYSICALLYBASEDBLOOMSCENE_H
