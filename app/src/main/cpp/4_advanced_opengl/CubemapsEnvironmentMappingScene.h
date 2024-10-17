//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_CUBEMAPSENVIRONMENTMAPPINGSCENE_H
#define LEARNGLES_CUBEMAPSENVIRONMENTMAPPINGSCENE_H

#include "BaseScene.h"



class Shader;

class CubemapsEnvironmentMappingScene : public BaseScene {
private:

    Shader *shader = nullptr;
    Shader *skyboxShader = nullptr;

    unsigned int SCR_WIDTH = 0u;
    unsigned int SCR_HEIGHT = 0u;
    // cube VAO
    unsigned int cubeVAO = 0U, cubeVBO = 0U;
    // skybox VAO
    unsigned int skyboxVAO = 0U, skyboxVBO = 0U;
    unsigned int cubemapTexture = 0U;
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_CUBEMAPSENVIRONMENTMAPPINGSCENE_H
