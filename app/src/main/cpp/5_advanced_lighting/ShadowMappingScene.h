//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_SHADOWMAPPINGSCENE_H
#define LEARNGLES_SHADOWMAPPINGSCENE_H

#include "Scene.h"
class ShadowMappingScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_SHADOWMAPPINGSCENE_H
