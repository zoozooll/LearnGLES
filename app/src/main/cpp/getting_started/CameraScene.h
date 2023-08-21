//
// Created by zoozo on 8/21/2023.
//

#ifndef LEARNGLES_CAMERASCENE_H
#define LEARNGLES_CAMERASCENE_H

#include "Scene.h"
#include "Camera.h"

class Shader;

class CameraScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

private:
    unsigned int texture1 = 0, texture2 = 0;
    unsigned int VBO = 0, VAO = 0;
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    Shader *ourShader = nullptr;
};


#endif //LEARNGLES_CAMERASCENE_H
