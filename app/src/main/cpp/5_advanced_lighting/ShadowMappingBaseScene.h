//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_SHADOWMAPPINGBASESCENE_H
#define LEARNGLES_SHADOWMAPPINGBASESCENE_H

#include "Scene.h"
class ShadowMappingBaseScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_SHADOWMAPPINGBASESCENE_H
