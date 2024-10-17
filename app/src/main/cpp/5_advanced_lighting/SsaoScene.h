//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_SSAOSCENE_H
#define LEARNGLES_SSAOSCENE_H

#include "BaseScene.h"
#include "SceneCommand.h"
#include "TargetCamera.h"
#include "SceneTouchEvent.h"
#include "Shader.h"
#include "Model.h"

class SsaoScene : public BaseScene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

private:

    Shader *shaderGeometryPass = nullptr;
    Shader *shaderLightingPass = nullptr;
    Shader *shaderSSAO = nullptr;
    Shader *shaderSSAOBlur = nullptr;

    Model *backpack = nullptr;
    void renderQuad();
    void renderCube();

    unsigned int quadVAO = 0;
    unsigned int quadVBO = 0;
    unsigned int cubeVAO = 0;
    unsigned int cubeVBO = 0;

    unsigned int gBuffer = 0;
    unsigned int ssaoFBO = 0;
    unsigned int ssaoBlurFBO = 0;
    unsigned int gPosition, gNormal, gAlbedo;
    unsigned int ssaoColorBuffer, ssaoColorBufferBlur;
    unsigned int rboDepth;
    unsigned int noiseTexture;

    std::vector<glm::vec3> ssaoKernel;
//    std::vector<glm::vec3> ssaoNoise;

    // lighting info
    // -------------
    glm::vec3 lightPos = glm::vec3(2.0, 4.0, -2.0);
    glm::vec3 lightColor = glm::vec3(0.2, 0.2, 0.7);
};


#endif //LEARNGLES_SSAOSCENE_H
