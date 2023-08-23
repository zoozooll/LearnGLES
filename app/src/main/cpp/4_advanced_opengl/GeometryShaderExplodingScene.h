//
// Created by huion on 2023/8/22.
//

#ifndef LEARNGLES_GEOMETRYSHADEREXPLODINGSCENE_H
#define LEARNGLES_GEOMETRYSHADEREXPLODINGSCENE_H

#include "Scene.h"
class GeometryShaderExplodingScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_GEOMETRYSHADEREXPLODINGSCENE_H
