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

    void move(const glm::vec2 &start_pivot, const glm::vec2 &end_pivot) override;

    void scale(const float &scale) override;

    void yawPitch(const glm::vec2 &director) override;

    void roll(const float &angle) override;

private:
    unsigned int texture1 = 0, texture2 = 0;
    unsigned int VAO = 0;
    Shader *ourShader = nullptr;
    glm::mat4 model = glm::mat4(1.0f);
};


#endif //LEARNGLES_COORDINATESYSTEMDEPTHSCENE_H
