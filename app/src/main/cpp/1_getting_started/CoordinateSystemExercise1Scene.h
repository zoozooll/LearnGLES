//
// Created by zoozo on 8/9/2023.
//

#ifndef LEARNGLES_COORDINATESYSTEMEXERCISE1SCENE_H
#define LEARNGLES_COORDINATESYSTEMEXERCISE1SCENE_H

#include "Scene.h"
#include "SceneTouchEvent.h"

class Shader;

class CoordinateSystemExercise1Scene : public Scene, public SceneTouchEvent {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    void roll(const float &angle) override;

private:
    unsigned int texture1 = 0, texture2 = 0;
    unsigned int VAO = 0;
    Shader *ourShader = nullptr;

    glm::mat4 model = glm::mat4(1.0f);
};


#endif //LEARNGLES_COORDINATESYSTEMEXERCISE1SCENE_H
