//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_NORMALMAPPINGSCENE_H
#define LEARNGLES_NORMALMAPPINGSCENE_H

#include "BaseScene.h"
#include <glm/glm.hpp>


class Shader;

class NormalMappingScene : public BaseScene {
private:
    unsigned int quadVAO = 0;
    unsigned int quadVBO = 0;

    Shader* shader = nullptr;


    unsigned int diffuseMap;
    unsigned int normalMap;

    // lighting info
    // -------------
    glm::vec3 lightPos = glm::vec3(0.5f, 1.0f, 0.3f);

    void renderQuad();
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_NORMALMAPPINGSCENE_H
