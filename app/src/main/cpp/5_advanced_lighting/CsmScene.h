//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_CSMSCENE_H
#define LEARNGLES_CSMSCENE_H

#include "BaseScene.h"


class Shader;

class CsmScene : public BaseScene {
private:

    Shader *shader = nullptr;
    // Setup cube VAO
    unsigned int cubeVAO, cubeVBO;
    // Setup plane VAO
    unsigned int planeVAO, planeVBO;
    unsigned int cubeTexture;
    unsigned int floorTexture;

public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_CSMSCENE_H
