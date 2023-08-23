//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_FRAMEBUFFERSSCENE_H
#define LEARNGLES_FRAMEBUFFERSSCENE_H

#include "Scene.h"
class FrameBuffersScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_FRAMEBUFFERSSCENE_H
