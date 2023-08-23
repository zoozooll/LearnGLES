//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_IBLIRRADIANCECONVERSIONSCENE_H
#define LEARNGLES_IBLIRRADIANCECONVERSIONSCENE_H

#include "Scene.h"
class IblIrradianceConversionScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_IBLIRRADIANCECONVERSIONSCENE_H
