//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_SKELETALANIMATIONSCENE_H
#define LEARNGLES_SKELETALANIMATIONSCENE_H

#include "Scene.h"
class SkeletalAnimationScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_SKELETALANIMATIONSCENE_H
