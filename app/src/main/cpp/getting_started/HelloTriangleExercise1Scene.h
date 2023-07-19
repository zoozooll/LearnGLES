//
// Created by zoozo on 7/19/2023.
//

#ifndef LEARNGLES_HELLOTRIANGLEEXERCISE1SCENE_H
#define LEARNGLES_HELLOTRIANGLEEXERCISE1SCENE_H

#include "Scene.h"

class HelloTriangleExercise1Scene : public Scene {
public:
    void init() override;

    void resize(int i, int i1) override;

    void draw() override;

    void destroy() override;

private:
    unsigned int VAO = 0;
    unsigned int shaderProgram = 0;
};


#endif //LEARNGLES_HELLOTRIANGLEEXERCISE1SCENE_H
