//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_FRAMEBUFFERSEXERCISE1SCENE_H
#define LEARNGLES_FRAMEBUFFERSEXERCISE1SCENE_H

#include "Scene.h"

#include "SceneTouchEvent.h"

class Shader;
class Camera;

class FramebuffersExercise1Scene : public Scene, public SceneTouchEvent {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    void move(const glm::vec2 &start_pivot, const glm::vec2 &end_pivot) override;

    void scale(const float &scale) override;

    void yawPitch(const glm::vec2 &director) override;

    void roll(const float &angle) override;

    void onDoubleClick(const glm::vec2 &point) override;

private:
    unsigned int SCR_WIDTH = 0, SCR_HEIGHT = 0;

    Shader *shader = nullptr;
    Shader *screenShader = nullptr;
    Camera *camera = nullptr;
    unsigned int cubeVAO, cubeVBO;
    unsigned int planeVAO, planeVBO;
    unsigned int quadVAO, quadVBO;
    unsigned int cubeTexture;
    unsigned int floorTexture;
    unsigned int framebuffer;
    unsigned int rbo;
    unsigned int textureColorbuffer;
};


#endif //LEARNGLES_FRAMEBUFFERSEXERCISE1SCENE_H
