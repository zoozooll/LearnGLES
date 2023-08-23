//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_BASICLIGHTINGSPECULARSCENE_H
#define LEARNGLES_BASICLIGHTINGSPECULARSCENE_H

#include "Scene.h"
class BasicLightingSpecularScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_BASICLIGHTINGSPECULARSCENE_H
