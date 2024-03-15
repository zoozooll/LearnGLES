//
// Created by zoozo on 8/9/2023.
//

#ifndef LEARNGLES_COORDINATESYSTEMEXERCISE4SCENE_H
#define LEARNGLES_COORDINATESYSTEMEXERCISE4SCENE_H

#include <glm/glm.hpp>

#include "Scene.h"
#include "SceneCommand.h"

class Shader;

class CoordinateSystemExercise4Scene : public Scene, public SceneCommand {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> sendCommand(std::map<std::string, std::any> map) override;

private:
    unsigned int texture1 = 0, texture2 = 0;
    unsigned int VAO = 0;
    Shader *ourShader = nullptr;

    glm::mat4 model = glm::mat4(1.0f);

    void translateX(float t);
    void translateY(float t);
    void translateZ(float t);
    void translate(glm::vec3 t);
    void rotateX(float d);
    void rotateY(float d);
    void rotateZ(float d);
    void rotate(glm::vec3 r);
    void scaleX(float s);
    void scaleY(float s);
    void scaleZ(float s);
    void scale(glm::vec3 s);

    void update();
};


#endif //LEARNGLES_COORDINATESYSTEMEXERCISE4SCENE_H
