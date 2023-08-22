//
// Created by zoozo on 7/19/2023.
//

#ifndef LEARNGLES_SHADERSINTERPOLATIONSCENE_H
#define LEARNGLES_SHADERSINTERPOLATIONSCENE_H

#include "Scene.h"

class ShadersInterpolationScene : public Scene {
public:
    void init() override;

    void resize(int i, int i1) override;

    void draw() override;

    void destroy() override;

private:
    unsigned int VAO;
    unsigned int shaderProgram;
};


#endif //LEARNGLES_SHADERSINTERPOLATIONSCENE_H
