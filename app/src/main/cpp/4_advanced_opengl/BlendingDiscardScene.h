//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_BLENDINGDISCARDSCENE_H
#define LEARNGLES_BLENDINGDISCARDSCENE_H

#include "Scene.h"
class BlendingDiscardScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_BLENDINGDISCARDSCENE_H
