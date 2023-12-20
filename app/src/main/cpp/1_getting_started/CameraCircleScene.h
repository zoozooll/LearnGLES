//
// Created by Aaron Lee on 2023/10/30.
//

#ifndef LEARNGLES_CAMERACIRCLESCENE_H
#define LEARNGLES_CAMERACIRCLESCENE_H

#include "Scene.h"
#include "TargetCamera.h"
#include "SceneTouchEvent.h"

class Shader;

class CameraCircleScene : public Scene, public SceneTouchEvent {
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    void move(const glm::vec2 &start_pivot, const glm::vec2 &end_pivot) override;

    void scale(const float &scale) override;

    void yawPitch(const glm::vec2 &director) override;

    void roll(const float &angle) override;

    void onDoubleClick(const glm::vec2 point) override;

public:
    void onSingleClick(const glm::vec2 point) override;

private:
    unsigned int texture1 = 0, texture2 = 0;
    unsigned int VBO = 0, VAO = 0;
    TargetCamera camera = TargetCamera();
    Shader *ourShader = nullptr;
};


#endif //LEARNGLES_CAMERACIRCLESCENE_H
