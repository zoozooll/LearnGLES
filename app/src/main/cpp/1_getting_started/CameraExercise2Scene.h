//
// Created by Aaron Lee on 2023/10/19.
//

#ifndef LEARNGLES_CAMERAEXERCISE2SCENE_H
#define LEARNGLES_CAMERAEXERCISE2SCENE_H

#include "Scene.h"
#include "SceneTouchEvent.h"
#include "MovableCamera.h"

class Shader;

class CameraExercise2Scene : public Scene, public SceneTouchEvent {
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
    MovableCamera camera = MovableCamera();
    Shader *ourShader = nullptr;
};


#endif //LEARNGLES_CAMERAEXERCISE2SCENE_H
