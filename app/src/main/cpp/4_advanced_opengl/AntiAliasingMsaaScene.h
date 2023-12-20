//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_ANTIALIASINGMSAASCENE_H
#define LEARNGLES_ANTIALIASINGMSAASCENE_H

#include "Scene.h"
class AntiAliasingMsaaScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_ANTIALIASINGMSAASCENE_H
