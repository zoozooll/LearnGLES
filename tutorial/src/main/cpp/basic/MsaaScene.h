#ifndef LEARNGLES_MSAASCENE_H
#define LEARNGLES_MSAASCENE_H

#include "Scene.h"

class Shader;
class Camera;

class MsaaScene : public Scene {
public :
    MsaaScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~MsaaScene();

private:
    Camera* m_camera = nullptr;
    Shader* m_pShader = nullptr;
    unsigned int m_cubeVAO = 0u;
    unsigned int m_cubeVBO = 0u;
};

#endif //LEARNGLES_MSAASCENE_H
