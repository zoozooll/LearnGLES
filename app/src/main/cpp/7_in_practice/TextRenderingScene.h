//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_TEXTRENDERINGSCENE_H
#define LEARNGLES_TEXTRENDERINGSCENE_H

#include "BaseScene.h"
class TextRenderingScene : public BaseScene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_TEXTRENDERINGSCENE_H
