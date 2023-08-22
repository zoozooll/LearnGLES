//
// Created by zoozo on 7/19/2023.
//

#ifndef LEARNGLES_TEXTURESSCENE_H
#define LEARNGLES_TEXTURESSCENE_H

#include "Scene.h"

class Shader;

class TexturesScene : public Scene {
public:
    void init() override;

    void resize(int i, int i1) override;

    void draw() override;

    void destroy() override;

private:
    unsigned int VAO, EBO;
    unsigned texture;
    Shader* ourShader = nullptr;
};


#endif //LEARNGLES_TEXTURESSCENE_H
