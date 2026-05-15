#ifndef LEARNGLES_NORMALMAPPINGSCENE_H
#define LEARNGLES_NORMALMAPPINGSCENE_H

#include "Scene.h"

class NormalMappingScene : public Scene {
public :
    NormalMappingScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~NormalMappingScene();
};

#endif //LEARNGLES_NORMALMAPPINGSCENE_H
