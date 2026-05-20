#ifndef LEARNGLES_HDRSCENE_H
#define LEARNGLES_HDRSCENE_H

#include "Scene.h"

#include <vector>

class Shader;
class Camera;

class HdrScene : public Scene {
public :
    HdrScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~HdrScene();

private:
    void renderQuad();
    void renderCube();

    Camera* camera = nullptr;
    Shader* m_pShader = nullptr;
    Shader* m_pHdrShader = nullptr;

    unsigned int m_cubeVAO = 0u;
    unsigned int m_cubeVBO = 0u;
    unsigned int m_quadVAO = 0u;
    unsigned int m_quadVBO = 0u;

    unsigned int m_woodTexture = 0u;
    unsigned int m_hdrFBO = 0u;
    unsigned int m_colorBuffer = 0u;
    unsigned int m_rboDepth = 0u;

    std::vector<glm::vec3> m_lightPositions;
    std::vector<glm::vec3> m_lightColors;

    bool hdr = false;
    float exposure = 0.f;
};

#endif //LEARNGLES_HDRSCENE_H
