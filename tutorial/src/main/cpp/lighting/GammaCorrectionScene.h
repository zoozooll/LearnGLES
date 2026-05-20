#ifndef LEARNGLES_GAMMACORRECTIONSCENE_H
#define LEARNGLES_GAMMACORRECTIONSCENE_H

#include "Scene.h"

class Camera;
class Shader;

class GammaCorrectionScene : public Scene {
public :
    GammaCorrectionScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~GammaCorrectionScene();

private:
    Camera* m_camera = nullptr;
    Shader* m_pShader = nullptr;
    unsigned int m_planeVAO;
    unsigned int m_planeVBO;
    unsigned int m_floorTexture;
    unsigned int m_floorTextureGammaCorrected;

    glm::vec3 m_lightPositions[4];
    glm::vec3 m_lightColors[4];
    bool gammaEnabled = false;
public:
    bool isGammaEnabled() const;

    void setGammaEnabled(bool gammaEnabled);
};

#endif //LEARNGLES_GAMMACORRECTIONSCENE_H
