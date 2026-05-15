#ifndef LEARNGLES_ASTEROIDSCENE_H
#define LEARNGLES_ASTEROIDSCENE_H

#include "Scene.h"

class AsteroidScene : public Scene {
public :
    AsteroidScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~AsteroidScene();
};

#endif //LEARNGLES_ASTEROIDSCENE_H
