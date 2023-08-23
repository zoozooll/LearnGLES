//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_ANTIALIASINGOFFSCREENSCENE_H
#define LEARNGLES_ANTIALIASINGOFFSCREENSCENE_H

#include "Scene.h"
class AntiAliasingOffscreenScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_ANTIALIASINGOFFSCREENSCENE_H
