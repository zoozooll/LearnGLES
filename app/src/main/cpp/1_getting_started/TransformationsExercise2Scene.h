//
// Created by zoozo on 7/25/2023.
//

#ifndef LEARNGLES_TRANSFORMATIONSEXERCISE2SCENE_H
#define LEARNGLES_TRANSFORMATIONSEXERCISE2SCENE_H

#include "Scene.h"
#include "SceneCommand.h"

class Shader;

class TransformationsExercise2Scene : public Scene, public SceneCommand {
public:
    void init() override;

    void resize(int i, int i1) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> sendCommand(std::map<std::string, std::any> map) override;

private:
    unsigned int texture1, texture2;
    Shader *ourShader = nullptr;
    unsigned int VBO, VAO, EBO;
    glm::mat4 transform = glm::mat4(1.0f);

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
};


#endif //LEARNGLES_TRANSFORMATIONSEXERCISE2SCENE_H
