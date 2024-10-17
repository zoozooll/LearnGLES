//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_CUBEMAPSKYBOXSCENE_H
#define LEARNGLES_CUBEMAPSKYBOXSCENE_H

#include "BaseScene.h"



class Shader;

class CubemapSkyboxScene : public BaseScene {
private:


    unsigned int SCR_WIDTH = 0u;
    unsigned int SCR_HEIGHT = 0u;
    Shader *shader = nullptr;
    Shader *skyboxShader = nullptr;

    // cube VAO
    unsigned int cubeVAO = 0u, cubeVBO = 0u;
    // skybox VAO
    unsigned int skyboxVAO = 0u, skyboxVBO = 0u;

    unsigned int cubeTexture = 0u;
    unsigned int cubemapTexture = 0U;


public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_CUBEMAPSKYBOXSCENE_H
