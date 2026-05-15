#ifndef LEARNGLES_PHONGVSBLINNSCENE_H
#define LEARNGLES_PHONGVSBLINNSCENE_H

#include "Scene.h"

class PhongVsBlinnScene : public Scene {
public :
    PhongVsBlinnScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~PhongVsBlinnScene();
};

#endif //LEARNGLES_PHONGVSBLINNSCENE_H
