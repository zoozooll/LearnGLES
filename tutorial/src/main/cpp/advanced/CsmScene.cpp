#include "CsmScene.h"

#include "Shader.h"
#include "TargetCamera.h"
#include "Texture.h"
#include "logutil.h"

CsmScene::CsmScene() {
    visualizerVAOs = std::vector<GLuint>(8, 0);
    visualizerVBOs = std::vector<GLuint>(8, 0);
    visualizerEBOs = std::vector<GLuint>(8, 0);
    std::random_device device;
    generator = std::mt19937(device());
}

void CsmScene::init() {
    m_camera = new TargetCamera;
    shadowCascadeLevels = { m_camera->getFar() / 50.0f, m_camera->getFar() / 25.0f, m_camera->getFar() / 10.0f,
            m_camera->getFar() / 2.0f };
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    shader = new Shader("shaders/csm/10.shadow_mapping.vert", "shaders/csm/10.shadow_mapping.frag");
    simpleDepthShader = new Shader("shaders/csm/10.shadow_mapping_depth.vert", "shaders/csm/10.shadow_mapping_depth.frag", "10.shadow_mapping_depth.geom");
    debugDepthQuad = new Shader("shaders/csm/10.debug_quad.vert", "shaders/csm/10.debug_quad_depth.frag");
    debugCascadeShader = new Shader("shaders/csm/10.debug_cascade.vert", "shaders/csm/10.debug_cascade.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float planeVertices[] = {
            // positions            // normals         // texcoords
            25.0f, -2.0f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
            -25.0f, -2.0f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
            -25.0f, -2.0f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
            25.0f, -2.0f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
            -25.0f, -2.0f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
            25.0f, -2.0f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
    };
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindVertexArray(0);

    // load textures
    // -------------
    woodTexture = loadTexture("textures/wood.png");

    // configure light FBO
    // -----------------------
    glGenFramebuffers(1, &lightFBO);

    glGenTextures(1, &lightDepthMaps);
    glBindTexture(GL_TEXTURE_2D_ARRAY, lightDepthMaps);
    glTexImage3D(
            GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT32F, depthMapResolution, depthMapResolution, int(shadowCascadeLevels.size()) + 1,
            0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    constexpr float bordercolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, bordercolor);

    glBindFramebuffer(GL_FRAMEBUFFER, lightFBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, lightDepthMaps, 0);
//    glDrawBuffer(GL_NONE); //TODO Not support in GLES
    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        LOGW(__FILE_NAME__, "ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // configure UBO
    // --------------------
    glGenBuffers(1, &matricesUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, matricesUBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4x4) * 16, nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, matricesUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // shader configuration
    // --------------------
    shader->use();
    shader->setInt("diffuseTexture", 0);
    shader->setInt("shadowMap", 1);
    debugDepthQuad->use();
    debugDepthQuad->setInt("depthMap", 0);
}

void CsmScene::resize(int width, int height) {
    m_camera->setAspec((float) width / (float) height);
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

void CsmScene::draw() {
    m_camera->update();
    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 0. UBO setup
    const auto lightMatrices = getLightSpaceMatrices();
    glBindBuffer(GL_UNIFORM_BUFFER, matricesUBO);
    for (size_t i = 0; i < lightMatrices.size(); ++i)
    {
        glBufferSubData(GL_UNIFORM_BUFFER, i * sizeof(glm::mat4x4), sizeof(glm::mat4x4), &lightMatrices[i]);
    }
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // 1. render depth of scene to texture (from light's perspective)
    // --------------------------------------------------------------
    simpleDepthShader->use();

    glBindFramebuffer(GL_FRAMEBUFFER, lightFBO);
    glViewport(0, 0, depthMapResolution, depthMapResolution);
    glClear(GL_DEPTH_BUFFER_BIT);
    glCullFace(GL_FRONT);  // peter panning
    renderScene(*simpleDepthShader);
    glCullFace(GL_BACK);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // reset viewport
    glViewport(0, 0, m_width, m_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 2. render scene as normal using the generated depth/shadow map
    // --------------------------------------------------------------
    shader->use();
    const glm::mat4 projection = m_camera->getProjectionMatrix();
    const glm::mat4 view = m_camera->getViewMatrix();
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    // set light uniforms
    shader->setVec3("viewPos", m_camera->getPosition());
    shader->setVec3("lightDir", lightDir);
    shader->setFloat("farPlane", m_camera->getFar());
    shader->setInt("cascadeCount", shadowCascadeLevels.size());
    for (size_t i = 0; i < shadowCascadeLevels.size(); ++i)
    {
        shader->setFloat("cascadePlaneDistances[" + std::to_string(i) + "]", shadowCascadeLevels[i]);
    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, woodTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D_ARRAY, lightDepthMaps);
    renderScene(*shader);

    if (lightMatricesCache.size() != 0)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        debugCascadeShader->use();
        debugCascadeShader->setMat4("projection", projection);
        debugCascadeShader->setMat4("view", view);
        drawCascadeVolumeVisualizers(lightMatricesCache, debugCascadeShader);
        glDisable(GL_BLEND);
    }

    // render Depth map to quad for visual debugging
    // ---------------------------------------------
    debugDepthQuad->use();
    debugDepthQuad->setInt("layer", debugLayer);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, lightDepthMaps);
    if (showQuad)
    {
        renderQuad();
    }
}

void CsmScene::destroy() {
    if (shader) delete shader;
    if (simpleDepthShader) delete simpleDepthShader;
    if (debugDepthQuad) delete debugDepthQuad;
    if (debugCascadeShader) delete debugCascadeShader;

    glDeleteVertexArrays(1, &planeVAO);
    glDeleteBuffers(1, &planeVBO);
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
    glDeleteTextures(1, &woodTexture);
    glDeleteTextures(1, &lightDepthMaps);
    glDeleteFramebuffers(1, &lightFBO);
    glDeleteBuffers(1, &matricesUBO);
    delete m_camera;
}

CsmScene::~CsmScene() {

}

std::map<std::string, std::any> CsmScene::propertyEvent(std::map<std::string, std::any> &map) {
    auto eventIdIt = map.find("event_id");
    if (eventIdIt != map.end() && eventIdIt->second.type() == typeid(std::string)) {
        auto eventIdStr = std::any_cast<std::string>(eventIdIt->second);
        if ("target_camera_touching_event" == eventIdStr) {
            parseTargetCameraEvent(map);
        }
    }
    return {};
}

void CsmScene::parseTargetCameraEvent(std::map<std::string, std::any> &event) {
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

glm::mat4 CsmScene::getLightSpaceMatrix(const float nearPlane, const float farPlane) {
    const auto proj = m_camera->getProjectionMatrix();
    const auto corners = getFrustumCornersWorldSpace(proj * m_camera->getViewMatrix());

    glm::vec3 center = glm::vec3(0, 0, 0);
    for (const auto& v : corners)
    {
        center += glm::vec3(v);
    }
    center /= corners.size();

    const auto lightView = glm::lookAt(center + lightDir, center, glm::vec3(0.0f, 1.0f, 0.0f));

    float minX = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float minY = std::numeric_limits<float>::max();
    float maxY = std::numeric_limits<float>::lowest();
    float minZ = std::numeric_limits<float>::max();
    float maxZ = std::numeric_limits<float>::lowest();
    for (const auto& v : corners)
    {
        const auto trf = lightView * v;
        minX = std::min(minX, trf.x);
        maxX = std::max(maxX, trf.x);
        minY = std::min(minY, trf.y);
        maxY = std::max(maxY, trf.y);
        minZ = std::min(minZ, trf.z);
        maxZ = std::max(maxZ, trf.z);
    }

    constexpr float zMult = 10.0f;
    if (minZ < 0) minZ *= zMult; else minZ /= zMult;
    if (maxZ < 0) maxZ /= zMult; else maxZ *= zMult;

    const glm::mat4 lightProjection = glm::ortho(minX, maxX, minY, maxY, minZ, maxZ);
    return lightProjection * lightView;
}

void CsmScene::renderCube() {
    if (cubeVAO == 0)
    {
        float vertices[] = {
                // back face
                -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
                1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
                1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
                1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
                -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
                -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
                // front face
                -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
                1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
                1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
                1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
                -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
                -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
                // left face
                -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
                -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
                -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
                -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
                -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
                -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
                // right face
                1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
                1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
                1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right
                1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
                1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
                1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left
                // bottom face
                -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
                1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
                1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
                1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
                -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
                -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
                // top face
                -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
                1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
                1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right
                1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
                -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
                -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left
        };
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindVertexArray(cubeVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void CsmScene::renderScene(const Shader &shader) {
// floor
    glm::mat4 model = glm::mat4(1.0f);
    shader.setMat4("model", model);
    glBindVertexArray(planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    static std::vector<glm::mat4> modelMatrices;
    if (modelMatrices.size() == 0)
    {
        for (int i = 0; i < 10; ++i)
        {
            std::uniform_real_distribution<float> offsetDistribution = std::uniform_real_distribution<float>(-10, 10);
            std::uniform_real_distribution<float> scaleDistribution = std::uniform_real_distribution<float>(1.0, 2.0);
            std::uniform_real_distribution<float> rotationDistribution = std::uniform_real_distribution<float>(0, 180);

            auto model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(offsetDistribution(generator), offsetDistribution(generator) + 10.0f, offsetDistribution(generator)));
            model = glm::rotate(model, glm::radians(rotationDistribution(generator)), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
            model = glm::scale(model, glm::vec3(scaleDistribution(generator)));
            modelMatrices.push_back(model);
        }
    }

    for (const auto& model : modelMatrices)
    {
        shader.setMat4("model", model);
        renderCube();
    }
}

void CsmScene::renderQuad() {
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

std::vector<glm::mat4> CsmScene::getLightSpaceMatrices() {
    std::vector<glm::mat4> ret;
    for (size_t i = 0; i < shadowCascadeLevels.size() + 1; ++i)
    {
        if (i == 0) ret.push_back(getLightSpaceMatrix(m_camera->getNear(), shadowCascadeLevels[i]));
        else if (i < shadowCascadeLevels.size()) ret.push_back(getLightSpaceMatrix(shadowCascadeLevels[i - 1], shadowCascadeLevels[i]));
        else ret.push_back(getLightSpaceMatrix(shadowCascadeLevels[i - 1], m_camera->getFar()));
    }
    return ret;
}

std::vector<glm::vec4> CsmScene::getFrustumCornersWorldSpace(const glm::mat4 &projview) {
    const auto inv = glm::inverse(projview);
    std::vector<glm::vec4> frustumCorners;
    for (unsigned int x = 0; x < 2; ++x)
    {
        for (unsigned int y = 0; y < 2; ++y)
        {
            for (unsigned int z = 0; z < 2; ++z)
            {
                const glm::vec4 pt = inv * glm::vec4(2.0f * x - 1.0f, 2.0f * y - 1.0f, 2.0f * z - 1.0f, 1.0f);
                frustumCorners.push_back(pt / pt.w);
            }
        }
    }
    return frustumCorners;
}

void CsmScene::drawCascadeVolumeVisualizers(const std::vector<glm::mat4> &lightMatrices, Shader *shader) {
    static std::vector<GLuint> visualizerVAOs(8, 0);
    static std::vector<GLuint> visualizerVBOs(8, 0);
    static std::vector<GLuint> visualizerEBOs(8, 0);

    const GLuint indices[] = {
            0, 2, 3, 0, 3, 1, 4, 6, 2, 4, 2, 0, 5, 7, 6, 5, 6, 4,
            1, 3, 7, 1, 7, 5, 6, 7, 3, 6, 3, 2, 1, 5, 4, 0, 1, 4
    };

    const glm::vec4 colors[] = {
            {1.0, 0.0, 0.0, 0.5f},
            {0.0, 1.0, 0.0, 0.5f},
            {0.0, 0.0, 1.0, 0.5f},
    };

    for (int i = 0; i < lightMatrices.size(); ++i)
    {
        const auto corners = getFrustumCornersWorldSpace(lightMatrices[i]);
        std::vector<glm::vec3> vec3s;
        for (const auto& v : corners) vec3s.push_back(glm::vec3(v));

        if (visualizerVAOs[i] == 0) {
            glGenVertexArrays(1, &visualizerVAOs[i]);
            glGenBuffers(1, &visualizerVBOs[i]);
            glGenBuffers(1, &visualizerEBOs[i]);
        }

        glBindVertexArray(visualizerVAOs[i]);
        glBindBuffer(GL_ARRAY_BUFFER, visualizerVBOs[i]);
        glBufferData(GL_ARRAY_BUFFER, vec3s.size() * sizeof(glm::vec3), &vec3s[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, visualizerEBOs[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

        shader->setVec4("color", colors[i % 3]);
        glDrawElements(GL_TRIANGLES, GLsizei(36), GL_UNSIGNED_INT, 0);
    }
}
