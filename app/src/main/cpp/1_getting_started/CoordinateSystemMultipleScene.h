//
// Created by zoozo on 8/9/2023.
//

#ifndef LEARNGLES_COORDINATESYSTEMMULTIPLESCENE_H
#define LEARNGLES_COORDINATESYSTEMMULTIPLESCENE_H

#include "Scene.h"

#include <glm/glm.hpp>

class Shader;

class CoordinateSystemMultipleScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

private:
    unsigned int texture1 = 0, texture2 = 0;
    unsigned int VAO = 0;
    Shader *ourShader = nullptr;

    // world space positions of our cubes
    glm::vec3 *cubePositions = nullptr;
};


#endif //LEARNGLES_COORDINATESYSTEMMULTIPLESCENE_H
