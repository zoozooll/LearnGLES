//
// Created by zoozo on 2026/5/11.
//

#ifndef LEARNGLES_BASICGLESSCENE_H
#define LEARNGLES_BASICGLESSCENE_H

#include "Scene.h"

class BasicGlesScene : public Scene {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

};


#endif //LEARNGLES_BASICGLESSCENE_H
