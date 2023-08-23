//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_DEFERREDSHADINGSCENE_H
#define LEARNGLES_DEFERREDSHADINGSCENE_H

#include "Scene.h"
class DeferredShadingScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_DEFERREDSHADINGSCENE_H
