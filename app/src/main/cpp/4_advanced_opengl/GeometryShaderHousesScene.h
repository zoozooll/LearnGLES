//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_GEOMETRYSHADERHOUSESSCENE_H
#define LEARNGLES_GEOMETRYSHADERHOUSESSCENE_H

#include "Scene.h"

class Camera;

class Shader;

class GeometryShaderHousesScene : public Scene {
private:
    Camera *camera = nullptr;
    Shader *shader = nullptr;
    int SCR_WIDTH = 0;
    int SCR_HEIGHT = 0;
    unsigned int VBO = 0U, VAO = 0U;

public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_GEOMETRYSHADERHOUSESSCENE_H
