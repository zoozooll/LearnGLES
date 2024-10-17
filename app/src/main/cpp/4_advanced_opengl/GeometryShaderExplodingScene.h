//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_GEOMETRYSHADEREXPLODINGSCENE_H
#define LEARNGLES_GEOMETRYSHADEREXPLODINGSCENE_H

#include "BaseScene.h"

class Shader;

class Model;

class GeometryShaderExplodingScene : public BaseScene {
private:

    Shader *shader = nullptr;
    Model *nanosuit = nullptr;
    float time = 0.F;

public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    void setTime(float time);
};


#endif //LEARNGLES_GEOMETRYSHADEREXPLODINGSCENE_H
