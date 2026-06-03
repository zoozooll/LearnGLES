#ifndef LEARNGLES_BLOOMSCENE_H
#define LEARNGLES_BLOOMSCENE_H

#include "TutorialScene.h"

#include <vector>

class Camera;
class Shader;

class BloomScene : public TutorialScene {
public :
    BloomScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~BloomScene();

    static constexpr unsigned int SCR_WIDTH = 800;
    static constexpr unsigned int SCR_HEIGHT = 600;

private:
    void renderQuad();
    void renderCube();

    Camera* m_camera = nullptr;
    Shader* m_pShader = nullptr;;
    Shader* m_pShaderLight = nullptr;;
    Shader* m_pShaderBlur = nullptr;;
    Shader* m_pShaderBloomFinal = nullptr;;

    unsigned int m_cubeVAO = 0u;
    unsigned int m_cubeVBO = 0u;
    unsigned int m_quadVAO = 0u;
    unsigned int m_quadVBO = 0u;

    unsigned int m_woodTexture = 0u;
    unsigned int m_containerTexture = 0u;

    unsigned int m_hdrFBO = 0u;
    unsigned int m_colorBuffers[2] = {0u, 0u};
    unsigned int m_rboDepth = 0u;

    unsigned int m_pingpongFBO[2] = {0u, 0u};
    unsigned int m_pingpongColorbuffers[2] = {0u, 0u};

    std::vector<glm::vec3> m_lightPositions;
    std::vector<glm::vec3> m_lightColors;
    int m_width = 0, m_height = 0;

    bool bloom = false;
    float exposure = 1.0f;

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_BLOOMSCENE_H
