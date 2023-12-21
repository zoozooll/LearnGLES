//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_POINTSHADOWSSCENE_H
#define LEARNGLES_POINTSHADOWSSCENE_H

#include "Scene.h"
#include "TargetCamera.h"
#include "SceneTouchEvent.h"

class Shader;

class PointShadowsScene : public Scene, public SceneTouchEvent {
private:
    // plane VAO
    unsigned int quadVAO = 0;

    Shader* simpleDepthShader = nullptr;
    Shader* shader = nullptr;
    int SHADOW_WIDTH = 0;
    int SHADOW_HEIGHT = 0;
    int SCR_WIDTH = 0;
    int SCR_HEIGHT = 0;
    TargetCamera camera = TargetCamera();

    unsigned int woodTexture = 0;
    glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
    unsigned int depthMapFBO = 0;
    unsigned int depthCubemap;
    // renderCube() renders a 1x1 3D cube in NDC.
    // -------------------------------------------------
    unsigned int cubeVAO = 0;

    void renderScene(const Shader &shader);
    void renderCube() const;

public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    void move(const glm::vec2 &start_pivot, const glm::vec2 &end_pivot) override;

    void scale(const float &scale) override;

    void yawPitch(const glm::vec2 &director) override;
};


#endif //LEARNGLES_POINTSHADOWSSCENE_H
