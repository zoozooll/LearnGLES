//
// Created by zoozo on 7/19/2023.
//

#ifndef LEARNGLES_SHADERSCLASSSCENE_H
#define LEARNGLES_SHADERSCLASSSCENE_H

#include "Scene.h"

class Shader;

class ShadersClassScene : public Scene {
public:
    void init() override;

    void resize(int i, int i1) override;

    void draw() override;

    void destroy() override;
private:
    Shader* ourShader;
    unsigned int VAO;
};


#endif //LEARNGLES_SHADERSCLASSSCENE_H
