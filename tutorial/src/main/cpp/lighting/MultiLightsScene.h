#ifndef LEARNGLES_MULTILIGHTSSCENE_H
#define LEARNGLES_MULTILIGHTSSCENE_H

#include "Scene.h"

class MultiLightsScene : public Scene {
public :
    MultiLightsScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~MultiLightsScene();
};

#endif //LEARNGLES_MULTILIGHTSSCENE_H
