//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_PARALLAXMAPPINGSCENE_H
#define LEARNGLES_PARALLAXMAPPINGSCENE_H

#include "BaseScene.h"


class Shader;


class ParallaxMappingScene : public BaseScene {
private:
    unsigned int quadVAO = 0;
    unsigned int quadVBO = 0;

    Shader* shader = nullptr;


    unsigned int diffuseMap;
    unsigned int normalMap;
    unsigned int heightMap;

    // lighting info
    // -------------
    glm::vec3 lightPos = glm::vec3(0.5f, 1.0f, 0.3f);

    float heightScale = 0.1f;

    void renderQuad();
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    void setHeightScale(float heightScale);
};


#endif //LEARNGLES_PARALLAXMAPPINGSCENE_H
