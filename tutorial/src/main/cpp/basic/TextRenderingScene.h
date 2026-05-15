#ifndef LEARNGLES_TEXTRENDERINGSCENE_H
#define LEARNGLES_TEXTRENDERINGSCENE_H

#include "Scene.h"

class TextRenderingScene : public Scene {
public :
    TextRenderingScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~TextRenderingScene();
};

#endif //LEARNGLES_TEXTRENDERINGSCENE_H
