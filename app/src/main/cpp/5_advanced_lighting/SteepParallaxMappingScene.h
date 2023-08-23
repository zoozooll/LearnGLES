//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_STEEPPARALLAXMAPPINGSCENE_H
#define LEARNGLES_STEEPPARALLAXMAPPINGSCENE_H

#include "Scene.h"
class SteepParallaxMappingScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_STEEPPARALLAXMAPPINGSCENE_H
