//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_GEOMETRYSHADERNORMALSSCENE_H
#define LEARNGLES_GEOMETRYSHADERNORMALSSCENE_H

#include "Scene.h"
class GeometryShaderNormalsScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_GEOMETRYSHADERNORMALSSCENE_H
