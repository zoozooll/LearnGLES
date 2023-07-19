//
// Created by zoozo on 7/19/2023.
//

#ifndef LEARNGLES_SHADERSUNIFORMSCENE_H
#define LEARNGLES_SHADERSUNIFORMSCENE_H

#include "Scene.h"

class ShadersUniformScene : public Scene {
public:
    void init() override;

    void resize(int i, int i1) override;

    void draw() override;

    void destroy() override;

private:
    unsigned int shaderProgram;
    unsigned int VAO;
};


#endif //LEARNGLES_SHADERSUNIFORMSCENE_H
