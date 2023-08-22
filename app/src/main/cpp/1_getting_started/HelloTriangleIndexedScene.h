//
// Created by zoozo on 7/19/2023.
//

#ifndef LEARNGLES_HELLOTRIANGLEINDEXEDSCENE_H
#define LEARNGLES_HELLOTRIANGLEINDEXEDSCENE_H

#include "Scene.h"

class HelloTriangleIndexedScene : public Scene {
public:
    void init() override;

    void resize(int i, int i1) override;

    void draw() override;

    void destroy() override;

private:
    unsigned int shaderProgram;
    unsigned int VAO, EBO;
};


#endif //LEARNGLES_HELLOTRIANGLEINDEXEDSCENE_H
