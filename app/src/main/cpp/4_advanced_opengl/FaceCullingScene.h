//
// Created by Aaron Lee on 2023/8/23.
//

#ifndef LEARNGLES_FACECULLINGSCENE_H
#define LEARNGLES_FACECULLINGSCENE_H

#include "Scene.h"
class FaceCullingScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_FACECULLINGSCENE_H
