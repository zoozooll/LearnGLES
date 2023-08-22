//
// Created by zoozo on 7/25/2023.
//

#ifndef LEARNGLES_TRANSFORMATIONSSCENE_H
#define LEARNGLES_TRANSFORMATIONSSCENE_H

#include "Scene.h"

class Shader;

class TransformationsScene : public Scene {
public:
    void init() override;

    void resize(int i, int i1) override;

    void draw() override;

    void destroy() override;

    void move(const glm::vec2 &start_pivot, const glm::vec2 &end_pivot) override;

    void scale(const float &scale) override;

    void yawPitch(const glm::vec2 &director) override;

    void roll(const float &angle) override;

private:
    unsigned int texture1, texture2;
    Shader *ourShader = nullptr;
    unsigned int VBO, VAO, EBO;
    glm::mat4 transform = glm::mat4(1.0f);
};


#endif //LEARNGLES_TRANSFORMATIONSSCENE_H
