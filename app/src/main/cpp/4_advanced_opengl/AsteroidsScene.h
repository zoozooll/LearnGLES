//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_ASTEROIDSSCENE_H
#define LEARNGLES_ASTEROIDSSCENE_H

#include "Scene.h"

class Camera;
class Shader;
class Model;

class AsteroidsScene : public Scene {
private:
    Camera* camera = nullptr;
    Model *rock = nullptr;
    Model *planet = nullptr;
    Shader *shader = nullptr;
    int SCR_WIDTH = 0;
    int SCR_HEIGHT = 0;
    unsigned int amount = 1000;
    glm::mat4* modelMatrices = nullptr;
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_ASTEROIDSSCENE_H
