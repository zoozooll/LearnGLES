#ifndef LEARNGLES_PHYSICALLYBASEDBLOOMSCENE_H
#define LEARNGLES_PHYSICALLYBASEDBLOOMSCENE_H

#include "Scene.h"

class PhysicallyBasedBloomScene : public Scene {
public :
    PhysicallyBasedBloomScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~PhysicallyBasedBloomScene();
};

#endif //LEARNGLES_PHYSICALLYBASEDBLOOMSCENE_H
