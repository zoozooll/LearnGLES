//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_ANTIALIASINGOFFSCREENSCENE_H
#define LEARNGLES_ANTIALIASINGOFFSCREENSCENE_H



class Shader;

#include "BaseScene.h"
class AntiAliasingOffscreenScene : public BaseScene {
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


#endif //LEARNGLES_ANTIALIASINGOFFSCREENSCENE_H
