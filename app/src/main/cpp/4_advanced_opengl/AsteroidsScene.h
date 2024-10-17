//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_ASTEROIDSSCENE_H
#define LEARNGLES_ASTEROIDSSCENE_H

#include "BaseScene.h"


class Shader;
class Model;

class AsteroidsScene : public BaseScene {
private:

    Model *rock = nullptr;
    Model *planet = nullptr;
    Shader *shader = nullptr;


    unsigned int amount = 1000;
    glm::mat4* modelMatrices = nullptr;
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_ASTEROIDSSCENE_H
