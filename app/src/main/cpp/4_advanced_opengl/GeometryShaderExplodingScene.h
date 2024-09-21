//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_GEOMETRYSHADEREXPLODINGSCENE_H
#define LEARNGLES_GEOMETRYSHADEREXPLODINGSCENE_H

#include "Scene.h"

class Camera;

class Shader;

class Model;

class GeometryShaderExplodingScene : public Scene {
private:
    Camera *camera = nullptr;
    Shader *shader = nullptr;
    Model *nanosuit = nullptr;
    int SCR_WIDTH = 0;
    int SCR_HEIGHT = 0;

    float time = 0.F;

public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    void setTime(float time);
};


#endif //LEARNGLES_GEOMETRYSHADEREXPLODINGSCENE_H
