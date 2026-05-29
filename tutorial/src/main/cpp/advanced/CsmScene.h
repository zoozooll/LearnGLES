#ifndef LEARNGLES_CSMSCENE_H
#define LEARNGLES_CSMSCENE_H

#include "TutorialScene.h"

#include <random>
#include <vector>

class Camera;
class Shader;

class CsmScene : public TutorialScene {
public :
    CsmScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~CsmScene();

private:
    Camera* m_camera = nullptr;
    Shader* shader = nullptr;
    Shader* simpleDepthShader = nullptr;
    Shader* debugDepthQuad = nullptr;
    Shader* debugCascadeShader = nullptr;

    unsigned int planeVAO = 0u, planeVBO = 0u;
    unsigned int cubeVAO = 0u, cubeVBO = 0u;
    unsigned int quadVAO = 0u, quadVBO = 0u;
    unsigned int woodTexture = 0u;
    unsigned int lightFBO = 0u;
    unsigned int lightDepthMaps = 0u;
    unsigned int matricesUBO = 0u;

    std::vector<unsigned int> visualizerVAOs;
    std::vector<unsigned int> visualizerVBOs;
    std::vector<unsigned int> visualizerEBOs;

    int m_width = 0;
    int m_height = 0;

    std::mt19937 generator;

    //Region Properties
    std::vector<float> shadowCascadeLevels;
    int debugLayer = 0;
    bool showQuad = false;
    std::vector<glm::mat4> lightMatricesCache;
    glm::vec3 lightDir = glm::normalize(glm::vec3(20.0f, 50, 20.0f));
    unsigned int depthMapResolution = 4096;
    //endregion

    void renderScene(const Shader &shader);
    void renderCube();
    void renderQuad();
    std::vector<glm::mat4> getLightSpaceMatrices();
    glm::mat4 getLightSpaceMatrix(const float nearPlane, const float farPlane);
    std::vector<glm::vec4> getFrustumCornersWorldSpace(const glm::mat4& projview);
    void drawCascadeVolumeVisualizers(const std::vector<glm::mat4>& lightMatrices, Shader* shader);

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_CSMSCENE_H
