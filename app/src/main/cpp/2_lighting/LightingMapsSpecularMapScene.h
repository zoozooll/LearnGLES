//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_LIGHTINGMAPSSPECULARMAPSCENE_H
#define LEARNGLES_LIGHTINGMAPSSPECULARMAPSCENE_H

#include "Scene.h"
#include "SceneTouchEvent.h"

class Camera;
class Shader;

class LightingMapsSpecularMapScene : public Scene, public SceneTouchEvent   {
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
};


#endif //LEARNGLES_LIGHTINGMAPSSPECULARMAPSCENE_H
