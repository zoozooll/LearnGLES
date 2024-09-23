//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_LIGHTINGSCENE_H
#define LEARNGLES_LIGHTINGSCENE_H

#include "Scene.h"

class Camera;
class Shader;

class LightingScene : public Scene {
private:
    Camera* camera = nullptr;
    Shader* shader = nullptr;

    void renderSphere();

    unsigned int sphereVAO = 0;
    unsigned int indexCount;

    const int nrRows    = 7;
    const int nrColumns = 7;
    const float spacing = 2.5;

    int SCR_WIDTH = 0;
    int SCR_HEIGHT = 0;

    // lights
// ------
    glm::vec3 lightPositions[4] = {
            glm::vec3(-10.0f,  10.0f, 10.0f),
            glm::vec3( 10.0f,  10.0f, 10.0f),
            glm::vec3(-10.0f, -10.0f, 10.0f),
            glm::vec3( 10.0f, -10.0f, 10.0f),
    };
    glm::vec3 lightColors[4] = {
            glm::vec3(300.0f, 300.0f, 300.0f),
            glm::vec3(300.0f, 300.0f, 300.0f),
            glm::vec3(300.0f, 300.0f, 300.0f),
            glm::vec3(300.0f, 300.0f, 300.0f)
    };


public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_LIGHTINGSCENE_H
