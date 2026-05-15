#ifndef LEARNGLES_IBLSCENE_H
#define LEARNGLES_IBLSCENE_H

#include "Scene.h"

class IblScene : public Scene {
public :
    IblScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~IblScene();
};

#endif //LEARNGLES_IBLSCENE_H
