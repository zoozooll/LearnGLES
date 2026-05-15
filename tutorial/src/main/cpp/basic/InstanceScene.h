#ifndef LEARNGLES_INSTANCESCENE_H
#define LEARNGLES_INSTANCESCENE_H

#include "Scene.h"

class InstanceScene : public Scene {
public :
    InstanceScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~InstanceScene();
};

#endif //LEARNGLES_INSTANCESCENE_H
