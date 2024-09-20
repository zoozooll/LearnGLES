//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_DEPTHTESTINGSCENE_H
#define LEARNGLES_DEPTHTESTINGSCENE_H

#include "SceneTouchEvent.h"
#include "SceneCommand.h"
#include "Scene.h"

class Camera;

class Shader;

class DepthTestingScene : public Scene, public SceneTouchEvent, public SceneCommand  {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    void move(const glm::vec2 &start_pivot, const glm::vec2 &end_pivot) override;

    void scale(const float &scale) override;

    void yawPitch(const glm::vec2 &director) override;

    void onDoubleClick(const glm::vec2 &point) override;

    std::map<std::string, std::any> sendCommand(std::map<std::string, std::any>) override;

private:
    Camera *camera = nullptr;
    int SCR_WIDTH = 0;
    int SCR_HEIGHT = 0;
    Shader *shader = nullptr;
    unsigned int cubeVAO = 0U, cubeVBO = 0u;
    unsigned int planeVAO = 0U, planeVBO= 0U;
    unsigned int cubeTexture = 0u;
    unsigned int floorTexture = 0u;
    bool depthTesting = true;
};


#endif //LEARNGLES_DEPTHTESTINGSCENE_H
