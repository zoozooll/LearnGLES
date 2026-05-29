#include "PhysicallyBasedBloomScene.h"

#include "Shader.h"
#include "TargetCamera.h"
#include "Texture.h"

static void _renderQuad(unsigned int& quadVAO, unsigned int& quadVBO)
{
    if (quadVAO == 0)
    {
        float quadVertices[] = {
                // positions        // texture Coords
                -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

PhysicallyBasedBloomScene::PhysicallyBasedBloomScene() {
}

void PhysicallyBasedBloomScene::init() {
    m_camera = new TargetCamera;
    glEnable(GL_DEPTH_TEST);
    shader = new Shader("shaders/physically_based_bloom/6.bloom.vert",
            "shaders/physically_based_bloom/6.bloom.frag");
    shaderLight = new Shader("shaders/physically_based_bloom/6.bloom.vert",
            "shaders/physically_based_bloom/6.light_box.frag");
    shaderBlur = new Shader("shaders/physically_based_bloom/6.old_blur.vert",
            "shaders/physically_based_bloom/6.old_blur.frag");
    shaderBloomFinal = new Shader("shaders/physically_based_bloom/6.bloom_final.vert",
            "shaders/physically_based_bloom/6.bloom_final.frag");

    woodTexture = loadTexture("textures/wood.png", true);
    containerTexture = loadTexture("textures/container2.png", true);

    glGenFramebuffers(1, &hdrFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    glGenTextures(2, colorBuffers);
    for (unsigned int i = 0; i < 2; i++)
    {
        glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_width, m_height, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
    }
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_width, m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glDrawBuffers(2, attachments);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glGenFramebuffers(2, pingpongFBO);
    glGenTextures(2, pingpongColorbuffers);
    for (unsigned int i = 0; i < 2; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
        glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_width, m_height, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);
    }

    lightPositions = { glm::vec3(0.0f, 0.5f, 1.5f),
            glm::vec3(-4.0f, 0.5f, -3.0f),
            glm::vec3(3.0f, 0.5f, 1.0f),
            glm::vec3(-.8f, 2.4f, -1.0f) };
    lightColors = { glm::vec3(5.0f, 5.0f, 5.0f),
            glm::vec3(10.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 15.0f),
            glm::vec3(0.0f, 5.0f, 0.0f) };

    shader->use();
    shader->setInt("diffuseTexture", 0);
    shaderBlur->use();
    shaderBlur->setInt("image", 0);
    shaderBloomFinal->use();
    shaderBloomFinal->setInt("scene", 0);
    shaderBloomFinal->setInt("bloomBlur", 1);

    bloomRenderer.Init(m_width, m_height);
}

void PhysicallyBasedBloomScene::resize(int width, int height) {
    m_camera->setAspec((float) width / (float) height);
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

void PhysicallyBasedBloomScene::draw() {
    m_camera->update();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 projection = m_camera->getProjectionMatrix();
    glm::mat4 view = m_camera->getViewMatrix();
    shader->use();
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, woodTexture);
    for (unsigned int i = 0; i < lightPositions.size(); i++)
    {
        shader->setVec3("lights[" + std::to_string(i) + "].Position", lightPositions[i]);
        shader->setVec3("lights[" + std::to_string(i) + "].Color", lightColors[i]);
    }
    shader->setVec3("viewPos", m_camera->getPosition());
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0));
    model = glm::scale(model, glm::vec3(12.5f, 0.5f, 12.5f));
    shader->setMat4("model", model);
    renderCube();
    glBindTexture(GL_TEXTURE_2D, containerTexture);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
    model = glm::scale(model, glm::vec3(0.5f));
    shader->setMat4("model", model); renderCube();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
    model = glm::scale(model, glm::vec3(0.5f));
    shader->setMat4("model", model); renderCube();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, -1.0f, 2.0));
    model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    shader->setMat4("model", model); renderCube();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 2.7f, 4.0));
    model = glm::rotate(model, glm::radians(23.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    model = glm::scale(model, glm::vec3(1.25)); shader->setMat4("model", model); renderCube();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-2.0f, 1.0f, -3.0));
    model = glm::rotate(model, glm::radians(124.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    shader->setMat4("model", model); renderCube();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0));
    model = glm::scale(model, glm::vec3(0.5f)); shader->setMat4("model", model); renderCube();

    shaderLight->use();
    shaderLight->setMat4("projection", projection);
    shaderLight->setMat4("view", view);
    for (unsigned int i = 0; i < lightPositions.size(); i++)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(lightPositions[i]));
        model = glm::scale(model, glm::vec3(0.25f));
        shaderLight->setMat4("model", model);
        shaderLight->setVec3("lightColor", lightColors[i]);
        renderCube();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    bool horizontal = true;
    if (programChoice == 2)
    {
        bool first_iteration = true;
        shaderBlur->use();
        for (unsigned int i = 0; i < 10; i++)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
            shaderBlur->setInt("horizontal", horizontal);
            glBindTexture(GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : pingpongColorbuffers[!horizontal]);
            renderQuad();
            horizontal = !horizontal;
            if (first_iteration) first_iteration = false;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    else if (programChoice == 3)
        bloomRenderer.RenderBloomTexture(colorBuffers[1], bloomFilterRadius);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shaderBloomFinal->use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
    glActiveTexture(GL_TEXTURE1);
    if (programChoice == 1)
        glBindTexture(GL_TEXTURE_2D, 0);
    else if (programChoice == 2)
        glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!horizontal]);
    else if (programChoice == 3)
        glBindTexture(GL_TEXTURE_2D, bloomRenderer.BloomTexture());
    shaderBloomFinal->setInt("programChoice", programChoice);
    shaderBloomFinal->setFloat("exposure", exposure);
    renderQuad();
}

void PhysicallyBasedBloomScene::destroy() {
    if (shader)
        delete shader;
    if (shaderLight)
        delete shaderLight;
    if (shaderBlur)
        delete shaderBlur;
    if (shaderBloomFinal)
        delete shaderBloomFinal;
    glDeleteTextures(1, &woodTexture);
    glDeleteTextures(1, &containerTexture);
    glDeleteTextures(2, colorBuffers);
    glDeleteFramebuffers(1, &hdrFBO);
    glDeleteRenderbuffers(1, &rboDepth);
    glDeleteTextures(2, pingpongColorbuffers);
    glDeleteFramebuffers(2, pingpongFBO);
    bloomRenderer.Destroy();
    glDeleteBuffers(1, &quadVBO);
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteVertexArrays(1, &cubeVAO);
    delete m_camera;
}

PhysicallyBasedBloomScene::~PhysicallyBasedBloomScene() {

}

std::map<std::string, std::any> PhysicallyBasedBloomScene::propertyEvent(std::map<std::string, std::any> &map) {
    auto eventIdIt = map.find("event_id");
    if (eventIdIt != map.end() && eventIdIt->second.type() == typeid(std::string)) {
        auto eventIdStr = std::any_cast<std::string>(eventIdIt->second);
        if ("target_camera_touching_event" == eventIdStr) {
            parseTargetCameraEvent(map);
        }
    }
    return {};
}

void PhysicallyBasedBloomScene::parseTargetCameraEvent(std::map<std::string, std::any> &event) {
    auto* targetCamera = dynamic_cast<TargetCamera*>(m_camera);
    if (!targetCamera) return;

    if (auto it = event.find("single_touching"); it != event.end()) {
        if (it->second.type() == typeid(std::vector<float>)) {
            const auto& val = std::any_cast<const std::vector<float>&>(it->second);
            if (val.size() >= 4) {
                targetCamera->onSingleTouching(glm::vec2(val[0], val[1]), glm::vec2(val[2], val[3]));
            }
        }
    }

    if (auto it = event.find("double_touching"); it != event.end()) {
        if (it->second.type() == typeid(std::vector<float>)) {
            const auto& val = std::any_cast<const std::vector<float>&>(it->second);
            if (val.size() >= 8) {
                targetCamera->onDoubleTouching(glm::vec2(val[0], val[1]), glm::vec2(val[2], val[3]),
                                               glm::vec2(val[4], val[5]), glm::vec2(val[6], val[7]));
            }
        }
    }

    if (event.find("reset") != event.end()) {
        targetCamera->reset();
    }
}

void PhysicallyBasedBloomScene::renderCube() {
    if (cubeVAO == 0)
    {
        float vertices[] = {
                -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
                1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
                1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
                1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
                -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
                -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
                -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
                1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
                1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
                1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
                -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
                -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
                -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
                -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
                -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
                -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
                1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
                1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
                1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
                1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
                1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
                -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
                1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
                1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
                1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
                -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
                -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
                -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
                1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
                1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
                1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
                -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
                -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f
        };
        glGenVertexArrays(1, &cubeVAO); glGenBuffers(1, &cubeVBO);
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO); glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindVertexArray(cubeVAO);
        glEnableVertexAttribArray(0); glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1); glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2); glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0); glBindVertexArray(0);
    }
    glBindVertexArray(cubeVAO); glDrawArrays(GL_TRIANGLES, 0, 36); glBindVertexArray(0);
}

void PhysicallyBasedBloomScene::renderQuad() {
    _renderQuad(quadVAO, quadVBO);
}

bloomFBO::bloomFBO() {

}

bloomFBO::~bloomFBO() {

}

bool bloomFBO::Init(unsigned int windowWidth, unsigned int windowHeight, unsigned int mipChainLength) {
    if (mInit)
        return true;
    glGenFramebuffers(1, &mFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
    glm::vec2 mipSize((float)windowWidth, (float)windowHeight);
    glm::ivec2 mipIntSize((int)windowWidth, (int)windowHeight);
    for (GLuint i = 0; i < mipChainLength; i++)
    {
        bloomMip mip;
        mipSize *= 0.5f;
        mipIntSize /= 2;
        mip.size = mipSize;
        mip.intSize = mipIntSize;
        glGenTextures(1, &mip.texture);
        glBindTexture(GL_TEXTURE_2D, mip.texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_R11F_G11F_B10F, (int)mipSize.x, (int)mipSize.y, 0, GL_RGB, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        mMipChain.emplace_back(mip);
    }
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mMipChain[0].texture, 0);
    unsigned int attachments[1] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, attachments);
    int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    mInit = true;
    return true;
}

void bloomFBO::Destroy() {
    for (int i = 0; i < (int)mMipChain.size(); i++) {
        glDeleteTextures(1, &mMipChain[i].texture);
    }
    glDeleteFramebuffers(1, &mFBO);
    mMipChain.clear();
    mInit = false;
}

void bloomFBO::BindForWriting() {
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
}

const std::vector<bloomMip> &bloomFBO::MipChain() const {
    return mMipChain;
}

BloomRenderer::BloomRenderer() {

}

BloomRenderer::~BloomRenderer() {

}

bool BloomRenderer::Init(unsigned int windowWidth, unsigned int windowHeight) {
    if (mInit)
        return true;
    mSrcViewportSize = glm::ivec2(windowWidth, windowHeight);
    mSrcViewportSizeFloat = glm::vec2((float)windowWidth, (float)windowHeight);
    const unsigned int num_bloom_mips = 6;
    if (!mFBO.Init(windowWidth, windowHeight, num_bloom_mips))
        return false;
    mDownsampleShader = new Shader("6.new_downsample.vert", "6.new_downsample.frag");
    mUpsampleShader = new Shader("6.new_upsample.vert", "6.new_upsample.frag");
    mDownsampleShader->use();
    mDownsampleShader->setInt("srcTexture", 0);
    mUpsampleShader->use();
    mUpsampleShader->setInt("srcTexture", 0);
    mInit = true;
    return true;
}

void BloomRenderer::Destroy() {
    mFBO.Destroy();
    delete mDownsampleShader;
    delete mUpsampleShader;
    glDeleteBuffers(1, &quadVBO);
    glDeleteVertexArrays(1, &quadVAO);
}

void BloomRenderer::RenderBloomTexture(unsigned int srcTexture, float filterRadius) {
    mFBO.BindForWriting();
    this->RenderDownsamples(srcTexture);
    this->RenderUpsamples(filterRadius);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, mSrcViewportSize.x, mSrcViewportSize.y);
}

unsigned int BloomRenderer::BloomTexture() {
    return mFBO.MipChain()[0].texture;
}

unsigned int BloomRenderer::BloomMip_i(int index) {
    const std::vector<bloomMip>& mipChain = mFBO.MipChain();
    int size = (int)mipChain.size();
    return mipChain[(index > size-1) ? size-1 : (index < 0) ? 0 : index].texture;
}

void BloomRenderer::RenderDownsamples(unsigned int srcTexture) {
    const std::vector<bloomMip>& mipChain = mFBO.MipChain();
    mDownsampleShader->use();
    mDownsampleShader->setVec2("srcResolution", mSrcViewportSizeFloat);
    if (mKarisAverageOnDownsample) mDownsampleShader->setInt("mipLevel", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, srcTexture);
    for (int i = 0; i < (int)mipChain.size(); i++)
    {
        const bloomMip& mip = mipChain[i];
        glViewport(0, 0, mip.size.x, mip.size.y);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mip.texture, 0);
        renderQuad();
        mDownsampleShader->setVec2("srcResolution", mip.size);
        glBindTexture(GL_TEXTURE_2D, mip.texture);
        if (i == 0)
            mDownsampleShader->setInt("mipLevel", 1);
    }
}

void BloomRenderer::RenderUpsamples(float filterRadius) {
    const std::vector<bloomMip>& mipChain = mFBO.MipChain();
    mUpsampleShader->use();
    mUpsampleShader->setFloat("filterRadius", filterRadius);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    glBlendEquation(GL_FUNC_ADD);
    for (int i = (int)mipChain.size() - 1; i > 0; i--)
    {
        const bloomMip& mip = mipChain[i];
        const bloomMip& nextMip = mipChain[i-1];
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mip.texture);
        glViewport(0, 0, nextMip.size.x, nextMip.size.y);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, nextMip.texture, 0);
        renderQuad();
    }
    glDisable(GL_BLEND);
}

void BloomRenderer::renderQuad() {
    _renderQuad(quadVAO, quadVBO);
}
