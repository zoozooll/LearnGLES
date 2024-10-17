//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_HDRSCENE_H
#define LEARNGLES_HDRSCENE_H

#include "BaseScene.h"

#include <vector>


class Shader;

class HdrScene : public BaseScene {
private:
    unsigned int quadVAO = 0;
    unsigned int quadVBO = 0;
    unsigned int cubeVAO = 0;
    unsigned int cubeVBO = 0;

    Shader* shader = nullptr;
    Shader* hdrShader = nullptr;


    unsigned int diffuseMap;
    unsigned int normalMap;
    unsigned int heightMap;
    unsigned int woodTexture;
    unsigned int hdrFBO;
    unsigned int rboDepth;
    unsigned int colorBuffer;
    bool hdr = true;
    float exposure = 1.0f;
    // lighting info
    // -------------
    std::vector<glm::vec3> lightPositions;
    std::vector<glm::vec3> lightColors;

    void renderQuad();

    void renderCube();
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    void setHdr(bool hdr);

    void setExposure(float exposure);
};


#endif //LEARNGLES_HDRSCENE_H
