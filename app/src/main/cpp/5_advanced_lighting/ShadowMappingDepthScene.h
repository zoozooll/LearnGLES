//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_SHADOWMAPPINGDEPTHSCENE_H
#define LEARNGLES_SHADOWMAPPINGDEPTHSCENE_H

#include "Scene.h"
class ShadowMappingDepthScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_SHADOWMAPPINGDEPTHSCENE_H
