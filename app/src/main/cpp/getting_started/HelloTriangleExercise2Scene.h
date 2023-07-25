//
// Created by zoozo on 7/19/2023.
//

#ifndef LEARNGLES_HELLOTRIANGLEEXERCISE2SCENE_H
#define LEARNGLES_HELLOTRIANGLEEXERCISE2SCENE_H

#include "Scene.h"

class HelloTriangleExercise2Scene : public Scene {
public:
    void init() override;

    void resize(int i, int i1) override;

    void draw() override;

    void destroy() override;

private:
    unsigned int VBOs[2], VAOs[2];
    unsigned int shaderProgram = 0;
};


#endif //LEARNGLES_HELLOTRIANGLEEXERCISE2SCENE_H
