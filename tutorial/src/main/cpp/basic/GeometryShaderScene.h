#ifndef LEARNGLES_GEOMETRYSHADERSCENE_H
#define LEARNGLES_GEOMETRYSHADERSCENE_H

#include "Scene.h"

class GeometryShaderScene : public Scene {
public :
    GeometryShaderScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~GeometryShaderScene();
};

#endif //LEARNGLES_GEOMETRYSHADERSCENE_H
