#ifndef LEARNGLES_COMPUTESHADERSCENE_H
#define LEARNGLES_COMPUTESHADERSCENE_H

#include "TutorialScene.h"

class Shader;

class ComputeShader;

class Camera;

class ComputeShaderScene : public TutorialScene {
public :
    ComputeShaderScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~ComputeShaderScene();

private:
    Camera *m_camera = nullptr;
    Shader* m_screenQuadShader = nullptr;
    ComputeShader* m_computeShader = nullptr;
    unsigned int m_texture = 0u;
    unsigned int m_quadVAO = 0u, m_quadVBO = 0u;
    int m_width = 0u;
    int m_height = 0u;
    int m_fCounter = 0u;

    void renderQuad();
};

#endif //LEARNGLES_COMPUTESHADERSCENE_H
