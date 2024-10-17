//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_BLOOMSCENE_H
#define LEARNGLES_BLOOMSCENE_H

#include "BaseScene.h"
#include <vector>



class Shader;

class BloomScene : public BaseScene {
private:
    void renderQuad();
    void renderCube();


    Shader *shader = nullptr;
    Shader *shaderLight = nullptr;
    Shader *shaderBlur = nullptr;
    Shader *shaderBloomFinal = nullptr;

    unsigned int hdrFBO;
    unsigned int woodTexture;
    unsigned int containerTexture;
    unsigned int pingpongFBO[2];
    unsigned int pingpongColorbuffers[2];
    unsigned int rboDepth;
    unsigned int colorBuffers[2];
    unsigned int quadVAO;
    unsigned int quadVBO;
    unsigned int cubeVAO;
    unsigned int cubeVBO;

    std::vector<glm::vec3> lightPositions;
    std::vector<glm::vec3> lightColors;



    bool bloom = true;
    float exposure = 1.0f;

public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    void setBloom(bool bloom);

    void setExposure(float exposure);
};


#endif //LEARNGLES_BLOOMSCENE_H
