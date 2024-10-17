//
// Created by Aaron Lee on 2023/08/03.
//

#ifndef LEARNGLES_MODELLOADINGSCENE_H
#define LEARNGLES_MODELLOADINGSCENE_H

#include <glm/glm.hpp>

#include "BaseScene.h"

class Shader;
class Model;

class ModelLoadingScene : public BaseScene {
public:
    void init() override;

    void resize(int i, int i1) override;

    void draw() override;

    void destroy() override;

private:
    Shader *ourShader = nullptr;
    Model *ourModel = nullptr;
    glm::mat4 model = glm::mat4(1.0f);
};


#endif //LEARNGLES_MODELLOADINGSCENE_H
