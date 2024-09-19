//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_LIGHTINGCASTERSSPOTSOFTSCENE_H
#define LEARNGLES_LIGHTINGCASTERSSPOTSOFTSCENE_H

#include "Scene.h"
#include "SceneTouchEvent.h"

class Camera;
class Shader;

class LightingCastersSpotSoftScene : public Scene, public SceneTouchEvent {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    void move(const glm::vec2 &start_pivot, const glm::vec2 &end_pivot) override;

    void scale(const float &scale) override;

    void yawPitch(const glm::vec2 &director) override;

    void onDoubleClick(const glm::vec2 &point) override;

private:

    unsigned int SCR_WIDTH = 0;
    unsigned int SCR_HEIGHT = 0;
    unsigned int VBO, cubeVAO;
    unsigned int lightCubeVAO;
    glm::vec3 lightPos;
    Camera *camera = nullptr;
    Shader *lightingShader = nullptr;
    Shader *lightCubeShader = nullptr;
    unsigned int diffuseMap;
    unsigned int specularMap = 0u;
    glm::vec3 cubePositions[10] {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };
};


#endif //LEARNGLES_LIGHTINGCASTERSSPOTSOFTSCENE_H
