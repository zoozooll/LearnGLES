#ifndef LEARNGLES_SKELETALANIMATIONSCENE_H
#define LEARNGLES_SKELETALANIMATIONSCENE_H

#include "Scene.h"

class SkeletalAnimationScene : public Scene {
public :
    SkeletalAnimationScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~SkeletalAnimationScene();
};

#endif //LEARNGLES_SKELETALANIMATIONSCENE_H
