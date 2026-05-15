#ifndef LEARNGLES_MSAASCENE_H
#define LEARNGLES_MSAASCENE_H

#include "Scene.h"

class MsaaScene : public Scene {
public :
    MsaaScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~MsaaScene();
};

#endif //LEARNGLES_MSAASCENE_H
