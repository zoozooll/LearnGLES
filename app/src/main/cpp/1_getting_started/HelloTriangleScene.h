//
// Created by zoozo on 7/18/2023.
//

#ifndef LEARNGLES_HELLOTRIANGLESCENE_H
#define LEARNGLES_HELLOTRIANGLESCENE_H

#include "Scene.h"

class HelloTriangleScene : public Scene {
public:
    void init() override;

    void resize(int i, int i1) override;

    void draw() override;

    void destroy() override;

private:
    unsigned int VAO;
    unsigned int shaderProgram;
};


#endif //LEARNGLES_HELLOTRIANGLESCENE_H
