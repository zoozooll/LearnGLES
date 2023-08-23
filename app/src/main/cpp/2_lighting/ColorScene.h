//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_COLORSCENE_H
#define LEARNGLES_COLORSCENE_H

#include "Scene.h"
class ColorScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_COLORSCENE_H
