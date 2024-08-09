//
// Created by Aaron Lee on 2023/10/30.
//

#ifndef LEARNGLES_FocalLengthAndFOVScene_H
#define LEARNGLES_FocalLengthAndFOVScene_H

#include "Scene.h"
#include "TargetCamera.h"
#include "SceneTouchEvent.h"
#include "SceneCommand.h"

class Shader;

class FocalLengthAndFOVScene : public Scene, public SceneTouchEvent, public SceneCommand {
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

    void onSingleClick(const glm::vec2 &point) override;

    std::map<std::string, std::any> sendCommand(std::map<std::string, std::any> map) override;

private:
    unsigned int texture1 = 0, texture2 = 0;
    unsigned int VBO = 0, VAO = 0;
    TargetCamera camera = TargetCamera();
    Shader *ourShader = nullptr;
};


#endif //LEARNGLES_FocalLengthAndFOVScene_H
