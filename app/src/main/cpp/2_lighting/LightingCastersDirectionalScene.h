//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_LIGHTINGCASTERSDIRECTIONALSCENE_H
#define LEARNGLES_LIGHTINGCASTERSDIRECTIONALSCENE_H

#include "Scene.h"
class LightingCastersDirectionalScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_LIGHTINGCASTERSDIRECTIONALSCENE_H
