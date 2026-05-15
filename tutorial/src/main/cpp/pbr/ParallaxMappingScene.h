#ifndef LEARNGLES_PARALLAXMAPPINGSCENE_H
#define LEARNGLES_PARALLAXMAPPINGSCENE_H

#include "Scene.h"

class ParallaxMappingScene : public Scene {
public :
    ParallaxMappingScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~ParallaxMappingScene();
};

#endif //LEARNGLES_PARALLAXMAPPINGSCENE_H
