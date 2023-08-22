//
// Created by zoozo on 7/18/2023.
//

#ifndef LEARNGLES_HELLOWINDOWCLEARSCENE_H
#define LEARNGLES_HELLOWINDOWCLEARSCENE_H

#include "Scene.h"

class HelloWindowClearScene : public Scene {
public:
    void init() override;

    void resize(int i, int i1) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_HELLOWINDOWCLEARSCENE_H
