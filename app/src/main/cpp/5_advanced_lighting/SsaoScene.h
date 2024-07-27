//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_SSAOSCENE_H
#define LEARNGLES_SSAOSCENE_H

#include "Scene.h"
#include "SceneCommand.h"
#include "TargetCamera.h"
#include "SceneTouchEvent.h"
#include "Shader.h"
#include "Model.h"

class SsaoScene : public Scene, public SceneCommand, public SceneTouchEvent  {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> sendCommand(std::map<std::string, std::any> map) override;

    void move(const glm::vec2 &start_pivot, const glm::vec2 &end_pivot) override;

    void scale(const float &scale) override;

    void yawPitch(const glm::vec2 &director) override;

    void roll(const float &angle) override;

    void onSingleClick(const glm::vec2 point) override;

    void onDoubleClick(const glm::vec2 point) override;

    void onLongPress(const glm::vec2 point) override;

private:
    TargetCamera camera = TargetCamera();
    Shader *shaderGeometryPass = nullptr;
    Shader *shaderLightingPass = nullptr;
    Shader *shaderSSAO = nullptr;
    Shader *shaderSSAOBlur = nullptr;

    Model *backpack = nullptr;

    int SCR_WIDTH = 0;
    int SCR_HEIGHT = 0;

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
