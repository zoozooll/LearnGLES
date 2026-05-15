#ifndef LEARNGLES_CSMSCENE_H
#define LEARNGLES_CSMSCENE_H

#include "Scene.h"

class CsmScene : public Scene {
public :
    CsmScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~CsmScene();
};

#endif //LEARNGLES_CSMSCENE_H
