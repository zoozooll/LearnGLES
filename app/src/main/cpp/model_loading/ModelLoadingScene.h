//
// Created by Aaron Lee on 2023/08/03.
//

#ifndef LEARNGLES_MODELLOADINGSCENE_H
#define LEARNGLES_MODELLOADINGSCENE_H

#include <glm/glm.hpp>

#include "Scene.h"
#include "Camera.h"

class Shader;
class Model;

class ModelLoadingScene : public Scene {
public:
    void init() override;

    void resize(int i, int i1) override;

    void draw() override;

    void destroy() override;

private:
    Shader *ourShader = nullptr;
    Model *ourModel = nullptr;
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
};


#endif //LEARNGLES_MODELLOADINGSCENE_H
