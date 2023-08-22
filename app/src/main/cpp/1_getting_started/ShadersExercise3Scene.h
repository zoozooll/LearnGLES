//
// Created by zoozo on 7/19/2023.
//

#ifndef LEARNGLES_SHADERSEXERCISE3SCENE_H
#define LEARNGLES_SHADERSEXERCISE3SCENE_H

#include "Scene.h"

class Shader;

class ShadersExercise3Scene : public Scene {
public:
    void init() override;

    void resize(int i, int i1) override;

    void draw() override;

    void destroy() override;
private:
    Shader* ourShader;
    unsigned int VAO;
};


#endif //LEARNGLES_SHADERSEXERCISE3SCENE_H
