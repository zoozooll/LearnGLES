#ifndef LEARNGLES_COMPUTESHADERSCENE_H
#define LEARNGLES_COMPUTESHADERSCENE_H

#include "Scene.h"

class ComputeShaderScene : public Scene {
public :
    ComputeShaderScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~ComputeShaderScene();
};

#endif //LEARNGLES_COMPUTESHADERSCENE_H
