//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_ANTIALIASINGOFFSCREENSCENE_H
#define LEARNGLES_ANTIALIASINGOFFSCREENSCENE_H

class Camera;

class Shader;

#include "Scene.h"
class AntiAliasingOffscreenScene : public Scene {
private:
    Camera *camera = nullptr;

    Shader *shader = nullptr;
    // setup cube VAO
    unsigned int cubeVAO, cubeVBO;

    int SCR_WIDTH = 0;
    int SCR_HEIGHT = 0;

public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_ANTIALIASINGOFFSCREENSCENE_H
