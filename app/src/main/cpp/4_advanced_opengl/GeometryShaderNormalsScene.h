//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_GEOMETRYSHADERNORMALSSCENE_H
#define LEARNGLES_GEOMETRYSHADERNORMALSSCENE_H

#include "Scene.h"

class Camera;

class Shader;

class Model;

class GeometryShaderNormalsScene : public Scene {
private:
    Camera *camera = nullptr;
    Shader *shader = nullptr;
    Shader *normalShader = nullptr;
    Model *backpack = nullptr;
    int SCR_WIDTH = 0;
    int SCR_HEIGHT = 0;

public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_GEOMETRYSHADERNORMALSSCENE_H
