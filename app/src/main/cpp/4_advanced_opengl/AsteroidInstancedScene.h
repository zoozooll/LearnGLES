//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_ASTEROIDINSTANCEDSCENE_H
#define LEARNGLES_ASTEROIDINSTANCEDSCENE_H

#include "BaseScene.h"


class Shader;
class Model;

class AsteroidInstancedScene : public BaseScene {
private:

    Shader* asteroidShader = nullptr;
    Shader* planetShader = nullptr;
    Model* rock = nullptr;
    Model* planet = nullptr;



    unsigned int amount = 1000;

    glm::mat4* modelMatrices = nullptr;

public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_ASTEROIDINSTANCEDSCENE_H
