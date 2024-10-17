//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_ANTIALIASINGMSAASCENE_H
#define LEARNGLES_ANTIALIASINGMSAASCENE_H

#include "BaseScene.h"



class Shader;

class AntiAliasingMsaaScene : public BaseScene {
private:


    Shader *shader = nullptr;
    // setup cube VAO
    unsigned int cubeVAO, cubeVBO;




public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_ANTIALIASINGMSAASCENE_H
