//
// Created by Aaron Lee on 2023/10/18.
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

    void yawPitch(const glm::vec2 &director) override;

    void onDoubleClick(const glm::vec2 point) override;

private:
    unsigned int texture1 = 0;
    unsigned int VBO = 0, VAO = 0;
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 8.0f));
    Shader *ourShader = nullptr;
    glm::mat4 curCameraTranslate = glm::mat4(1.0f);
};


#endif //LEARNGLES_CAMERAEXERCISE1SCENE_H
