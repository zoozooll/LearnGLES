//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_GAMMACORRECTIONSCENE_H
#define LEARNGLES_GAMMACORRECTIONSCENE_H

#include "Scene.h"

class Shader;

class Camera;

class GammaCorrectionScene : public Scene {
private:
    Camera* camera = nullptr;
    Shader* shader = nullptr;
    // plane VAO
    unsigned int planeVAO, planeVBO;
    unsigned int floorTexture;
    unsigned int floorTextureGammaCorrected;
    int SCR_WIDTH = 0;
    int SCR_HEIGHT = 0;

    // lighting info
    // -------------
    glm::vec3 lightPositions[4] = {
            glm::vec3(-3.0f, 0.0f, 0.0f),
            glm::vec3(-1.0f, 0.0f, 0.0f),
            glm::vec3 (1.0f, 0.0f, 0.0f),
            glm::vec3 (3.0f, 0.0f, 0.0f)
    };

    glm::vec3 lightColors[4] = {
            glm::vec3(0.25),
            glm::vec3(0.50),
            glm::vec3(0.75),
            glm::vec3(1.00)
    };

    bool gammaEnabled = false;

public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    void setGammaEnabled(bool gammaEnabled);
};


#endif //LEARNGLES_GAMMACORRECTIONSCENE_H
