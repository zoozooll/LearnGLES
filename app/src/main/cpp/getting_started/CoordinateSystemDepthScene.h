//
// Created by zoozo on 8/9/2023.
//

#ifndef LEARNGLES_COORDINATESYSTEMDEPTHSCENE_H
#define LEARNGLES_COORDINATESYSTEMDEPTHSCENE_H

#include "Scene.h"

class Shader;

class CoordinateSystemDepthScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

private:
    unsigned int texture1 = 0, texture2 = 0;
    unsigned int VAO = 0;
    Shader *ourShader = nullptr;
};


#endif //LEARNGLES_COORDINATESYSTEMDEPTHSCENE_H
