//
// Created by zoozo on 7/19/2023.
//

#ifndef LEARNGLES_TEXTURECOMBINEDSCENE_H
#define LEARNGLES_TEXTURECOMBINEDSCENE_H

#include "Scene.h"

class Shader;

class TextureCombinedScene : public Scene {
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


#endif //LEARNGLES_TEXTURECOMBINEDSCENE_H
