//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_PARALLAXMAPPINGSCENE_H
#define LEARNGLES_PARALLAXMAPPINGSCENE_H

#include "Scene.h"
class ParallaxMappingScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_PARALLAXMAPPINGSCENE_H
