//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_BLENDINGDISCARDSCENE_H
#define LEARNGLES_BLENDINGDISCARDSCENE_H

#include "Scene.h"

class Camera;

class Shader;

class BlendingDiscardScene : public Scene {
private:
    Camera *camera = nullptr;

    unsigned int SCR_WIDTH = 0u;
    unsigned int SCR_HEIGHT = 0u;

    Shader *shader = nullptr;
    // cube VAO
    unsigned int cubeVAO = 0u, cubeVBO = 0u;
    // plane VAO
    unsigned int planeVAO = 0u, planeVBO = 0u;
    // transparent VAO
    unsigned int transparentVAO = 0u, transparentVBO = 0u;
    unsigned int cubeTexture = 0u;
    unsigned int floorTexture = 0u;
    unsigned int transparentTexture = 0u;
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_BLENDINGDISCARDSCENE_H
