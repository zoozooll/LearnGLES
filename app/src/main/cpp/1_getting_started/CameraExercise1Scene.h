//
// Created by huion on 2023/10/18.
//

#ifndef LEARNGLES_CAMERAEXERCISE1SCENE_H
#define LEARNGLES_CAMERAEXERCISE1SCENE_H

#include "Scene.h"
#include "SceneTouchEvent.h"
#include "Camera.h"

class Shader;

class CameraExercise1Scene : public Scene, public SceneTouchEvent {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    void move(const glm::vec2 &start_pivot, const glm::vec2 &end_pivot) override;

    void scale(const float &scale) override;

    void yawPitch(const glm::vec2 &director) override;

    void roll(const float &angle) override;

    void onDoubleClick(const glm::vec2 point) override;

private:
    unsigned int texture1 = 0;
    unsigned int VBO = 0, VAO = 0;
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    Shader *ourShader = nullptr;
};


#endif //LEARNGLES_CAMERAEXERCISE1SCENE_H
