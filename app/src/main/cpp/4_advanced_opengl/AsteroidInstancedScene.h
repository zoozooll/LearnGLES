//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_ASTEROIDINSTANCEDSCENE_H
#define LEARNGLES_ASTEROIDINSTANCEDSCENE_H

#include "Scene.h"
class AsteroidInstancedScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_ASTEROIDINSTANCEDSCENE_H
