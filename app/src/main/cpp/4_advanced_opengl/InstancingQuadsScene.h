//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_INSTANCINGQUADSSCENE_H
#define LEARNGLES_INSTANCINGQUADSSCENE_H

#include "Scene.h"

class Camera;
class Shader;

class InstancingQuadsScene : public Scene {
private:
    Camera* camera = nullptr;
    int SCR_WIDTH = 0;
    int SCR_HEIGHT = 0;

    Shader *shader = nullptr;

    unsigned int instanceVBO = 0U;
    unsigned int quadVAO = 0u, quadVBO = 0u;

public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_INSTANCINGQUADSSCENE_H
