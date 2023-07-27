//
// Created by Aaron Lee on 2023/07/27.
//

#ifndef LEARNGLES_TEXTUREEXERCISE4SCENE_H
#define LEARNGLES_TEXTUREEXERCISE4SCENE_H

#include "Scene.h"

class Shader;

class TextureExercise4Scene : public Scene {
public:
    void init() override;

    void resize(int i, int i1) override;

    void draw() override;

    void destroy() override;

private:
    Shader *ourShader = nullptr;
    unsigned int VBO, VAO, EBO;
    unsigned int texture1, texture2;
};


#endif //LEARNGLES_TEXTUREEXERCISE4SCENE_H
