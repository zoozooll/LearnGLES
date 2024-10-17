//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_GEOMETRYSHADERNORMALSSCENE_H
#define LEARNGLES_GEOMETRYSHADERNORMALSSCENE_H

#include "BaseScene.h"



class Shader;

class Model;

class GeometryShaderNormalsScene : public BaseScene {
private:

    Shader *shader = nullptr;
    Shader *normalShader = nullptr;
    Model *backpack = nullptr;

public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_GEOMETRYSHADERNORMALSSCENE_H
