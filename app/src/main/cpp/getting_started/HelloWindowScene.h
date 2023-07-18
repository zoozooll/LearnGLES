//
// Created by zoozo on 7/18/2023.
//

#ifndef LEARNGLES_HELLOWINDOWSCENE_H
#define LEARNGLES_HELLOWINDOWSCENE_H

#include "Scene.h"

class HelloWindowScene : public Scene {
public:
    void init() override;

    void resize(int i, int i1) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_HELLOWINDOWSCENE_H
