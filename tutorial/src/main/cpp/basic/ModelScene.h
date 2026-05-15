#ifndef LEARNGLES_MODELSCENE_H
#define LEARNGLES_MODELSCENE_H

#include "Scene.h"

class ModelScene : public Scene {
public :
    ModelScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~ModelScene();
};

#endif //LEARNGLES_MODELSCENE_H
