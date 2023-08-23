//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_DEFERREDSHADINGVOLUMESSCENE_H
#define LEARNGLES_DEFERREDSHADINGVOLUMESSCENE_H

#include "Scene.h"
class DeferredShadingVolumesScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_DEFERREDSHADINGVOLUMESSCENE_H
