#ifndef LEARNGLES_DEBUGGINGSCENE_H
#define LEARNGLES_DEBUGGINGSCENE_H

#include "Scene.h"

class DebuggingScene : public Scene {
public :
    DebuggingScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~DebuggingScene();
};

#endif //LEARNGLES_DEBUGGINGSCENE_H
