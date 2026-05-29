#ifndef LEARNGLES_PHYSICALLYBASEDBLOOMSCENE_H
#define LEARNGLES_PHYSICALLYBASEDBLOOMSCENE_H

#include <vector>

#include "TutorialScene.h"

struct bloomMip
{
    glm::vec2 size;
    glm::ivec2 intSize;
    unsigned int texture;
};

class Shader;
class Camera;

class bloomFBO
{
public:
    bloomFBO();
    ~bloomFBO();
    bool Init(unsigned int windowWidth, unsigned int windowHeight, unsigned int mipChainLength);
    void Destroy();
    void BindForWriting();
    const std::vector<bloomMip>& MipChain() const;

private:
    bool mInit = false;
    unsigned int mFBO = 0u;
    std::vector<bloomMip> mMipChain;
};

class BloomRenderer
{
public:
    BloomRenderer();
    ~BloomRenderer();
    bool Init(unsigned int windowWidth, unsigned int windowHeight);
    void Destroy();
    void RenderBloomTexture(unsigned int srcTexture, float filterRadius);
    unsigned int BloomTexture();
    unsigned int BloomMip_i(int index);

private:
    void renderQuad();
    void RenderDownsamples(unsigned int srcTexture);
    void RenderUpsamples(float filterRadius);

    bool mInit = false;
    bloomFBO mFBO;
    unsigned int quadVAO = 0u;
    unsigned int quadVBO = 0u;
    unsigned int cubeVAO = 0u;
    unsigned int cubeVBO = 0u;
    glm::ivec2 mSrcViewportSize;
    glm::vec2 mSrcViewportSizeFloat;
    Shader* mDownsampleShader = nullptr;
    Shader* mUpsampleShader = nullptr;

    bool mKarisAverageOnDownsample = true;
};

class PhysicallyBasedBloomScene : public TutorialScene {
public :
    PhysicallyBasedBloomScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~PhysicallyBasedBloomScene();

private:
    Camera* camera = nullptr;
    Shader* shader = nullptr;
    Shader* shaderLight = nullptr;
    Shader* shaderBlur = nullptr;
    Shader* shaderBloomFinal = nullptr;

    unsigned int woodTexture = 0u, containerTexture = 0u;
    unsigned int hdrFBO = 0u;
    unsigned int colorBuffers[2] = {0};
    unsigned int rboDepth = 0u;
    unsigned int pingpongFBO[2] = {0};
    unsigned int pingpongColorbuffers[2] = {0};
    unsigned int quadVAO = 0u;
    unsigned int quadVBO = 0u;
    unsigned int cubeVAO = 0u;
    unsigned int cubeVBO = 0u;

    std::vector<glm::vec3> lightPositions;
    std::vector<glm::vec3> lightColors;

    BloomRenderer bloomRenderer;

    int m_width = 0;
    int m_height = 0;

    //region Properties
    bool bloom;
    float exposure;
    int programChoice;
    float bloomFilterRadius;
    //endregion

    void renderCube();
    void renderQuad();
    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_PHYSICALLYBASEDBLOOMSCENE_H
