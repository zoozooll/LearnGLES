//
// Created by zoozo on 7/25/2023.
//

#ifndef LEARNGLES_TRANSFORMATIONSEXERCISE1SCENE_H
#define LEARNGLES_TRANSFORMATIONSEXERCISE1SCENE_H

#include "Scene.h"

class Shader;

class TransformationsExercise1Scene : public Scene {
public:
    void init() override;

    void resize(int i, int i1) override;

    void draw() override;

    void destroy() override;

private:
    unsigned int texture1, texture2;
    Shader *ourShader = nullptr;
    unsigned int VBO, VAO, EBO;
};


#endif //LEARNGLES_TRANSFORMATIONSEXERCISE1SCENE_H
