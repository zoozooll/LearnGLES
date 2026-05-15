#ifndef LEARNGLES_OITSCENE_H
#define LEARNGLES_OITSCENE_H

#include "Scene.h"

class OitScene : public Scene {
public :
    OitScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~OitScene();
};

#endif //LEARNGLES_OITSCENE_H
