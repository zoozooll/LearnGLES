//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_SHADOWMAPPINGSCENE_H
#define LEARNGLES_SHADOWMAPPINGSCENE_H

#include "BaseScene.h"
#include "TargetCamera.h"
#include "SceneTouchEvent.h"

class Shader;

class ShadowMappingScene : public BaseScene {

private:
    // plane VAO
    unsigned int planeVAO = 0;
    unsigned int quadVAO = 0;

    Shader* simpleDepthShader = nullptr;
    Shader* shader = nullptr;
    int SHADOW_WIDTH = 0;
    int SHADOW_HEIGHT = 0;




    unsigned int woodTexture = 0;
    glm::vec3 lightPos = glm::vec3(-2.0f, 4.0f, -1.0f);
    unsigned int depthMapFBO = 0;
    unsigned int depthMap;
    // renderCube() renders a 1x1 3D cube in NDC.
    // -------------------------------------------------
    unsigned int cubeVAO = 0;

    void renderQuad() const;
    void renderScene(const Shader &shader);
    void renderCube() const;

public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_SHADOWMAPPINGSCENE_H
