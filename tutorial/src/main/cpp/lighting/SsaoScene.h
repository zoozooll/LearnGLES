#ifndef LEARNGLES_SSAOSCENE_H
#define LEARNGLES_SSAOSCENE_H

#include "TutorialScene.h"

#include <vector>
#include <glm/glm.hpp>

class Camera;
class Shader;
class Model;

class SsaoScene : public TutorialScene {
public :
    static constexpr int SCR_WIDTH = 800;
    static constexpr int SCR_HEIGHT = 600;

    SsaoScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~SsaoScene();

private:
    void renderQuad();
    void renderCube();
    float ourLerp(float a, float b, float f);

    Camera* m_camera = nullptr;
    Shader* m_pShaderGeometryPass = nullptr;
    Shader* m_pShaderLightingPass = nullptr;
    Shader* m_pShaderSSAO = nullptr;
    Shader* m_pShaderSSAOBlur = nullptr;

    Model* m_pBackpack = nullptr;

    unsigned int m_gBuffer = 0u;
    unsigned int m_gPosition = 0u, m_gNormal = 0u, m_gAlbedo = 0u;
    unsigned int m_ssaoFBO = 0u, m_ssaoBlurFBO = 0u;
    unsigned int m_ssaoColorBuffer = 0u, m_ssaoColorBufferBlur = 0u;
    unsigned int m_rboDepth = 0u;

    std::vector<glm::vec3> m_ssaoKernel;
    unsigned int m_noiseTexture = 0u;

    unsigned int m_cubeVAO = 0u;
    unsigned int m_cubeVBO = 0u;
    unsigned int m_quadVAO = 0u;
    unsigned int m_quadVBO = 0u;
    int m_width = 0, m_height = 0;

    glm::vec3 m_lightPos = glm::vec3(2.0, 4.0, -2.0);
    glm::vec3 m_lightColor = glm::vec3(0.7 , 0.2, 0.7);

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_SSAOSCENE_H
