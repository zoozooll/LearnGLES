#include "BloomScene.h"

#include "Shader.h"
#include "Texture.h"
#include "TargetCamera.h"

BloomScene::BloomScene() {
}

void BloomScene::init() {
    m_camera = new TargetCamera;
    // configure global opengl state
    // -----------------------------
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    m_pShader = new Shader("shaders/bloom/bloom.vert", "shaders/bloom/bloom.frag");
    m_pShaderLight = new Shader("shaders/bloom/bloom.vert", "shaders/bloom/light_box.frag");
    m_pShaderBlur = new Shader("shaders/bloom/blur.vert", "shaders/bloom/blur.frag");
    m_pShaderBloomFinal = new Shader("shaders/bloom/bloom_final.vert", "shaders/bloom/bloom_final.frag");

    // load textures
    // -------------
    // note that we're loading the texture as an SRGB texture
    m_woodTexture      = loadTexture("textures/wood.png", true);
    // note that we're loading the texture as an SRGB texture
    m_containerTexture = loadTexture("textures/container2.png", true);

    // configure (floating point) framebuffers
    // ---------------------------------------
    glGenFramebuffers(1, &m_hdrFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_hdrFBO);
    // create 2 floating point color buffers (1 for normal rendering, other for brightness threshold values)
    glGenTextures(2, m_colorBuffers);
    for (unsigned int i = 0; i < 2; i++)
    {
        glBindTexture(GL_TEXTURE_2D, m_colorBuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // attach texture to framebuffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_colorBuffers[i], 0);
    }
    // create and attach depth buffer (renderbuffer)
    glGenRenderbuffers(1, &m_rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rboDepth);
    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
    unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glDrawBuffers(2, attachments);
    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        LOGI(__FILE_NAME__, "Framebuffer not complete!")    ;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // ping-pong-framebuffer for blurring
    glGenFramebuffers(2, m_pingpongFBO);
    glGenTextures(2, m_pingpongColorbuffers);
    for (unsigned int i = 0; i < 2; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_pingpongFBO[i]);
        glBindTexture(GL_TEXTURE_2D, m_pingpongColorbuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_pingpongColorbuffers[i], 0);
        // also check if framebuffers are complete (no need for depth buffer)
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            LOGI(__FILE_NAME__, "Framebuffer not complete!");
    }

    // lighting info
    // -------------
    m_lightPositions.emplace_back(glm::vec3( 0.0f, 0.5f,  1.5f));
    m_lightPositions.emplace_back(glm::vec3(-4.0f, 0.5f, -3.0f));
    m_lightPositions.emplace_back(glm::vec3( 3.0f, 0.5f,  1.0f));
    m_lightPositions.emplace_back(glm::vec3(-.8f,  2.4f, -1.0f));
    // colors
    m_lightColors.emplace_back(glm::vec3(5.0f,   5.0f,  5.0f));
    m_lightColors.emplace_back(glm::vec3(10.0f,  0.0f,  0.0f));
    m_lightColors.emplace_back(glm::vec3(0.0f,   0.0f,  15.0f));
    m_lightColors.emplace_back(glm::vec3(0.0f,   5.0f,  0.0f));

    // shader configuration
    // --------------------
    m_pShader->use();
    m_pShader->setInt("diffuseTexture", 0);
    m_pShaderBlur->use();
    m_pShaderBlur->setInt("image", 0);
    m_pShaderBloomFinal->use();
    m_pShaderBloomFinal->setInt("scene", 0);
    m_pShaderBloomFinal->setInt("bloomBlur", 1);
}

void BloomScene::resize(int width, int height) {
    m_camera->setAspec((float) width / (float) height);
    glViewport(0, 0, width, height);
    m_width = width;
    m_height = height;
}

void BloomScene::draw() {
    m_camera->update();
    // render
    // ------
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 1. render scene into floating point framebuffer
    // -----------------------------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, m_hdrFBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glm::mat4 projection = m_camera->getProjectionMatrix();
    glm::mat4 view = m_camera->getViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    if(m_pShader)
    {
        m_pShader->use();
        m_pShader->setMat4("projection", projection);
        m_pShader->setMat4("view", view);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_woodTexture);
        // set lighting uniforms
        for (unsigned int i = 0; i < m_lightPositions.size(); i++)
        {
            m_pShader->setVec3("lights[" + std::to_string(i) + "].Position", m_lightPositions[i]);
            m_pShader->setVec3("lights[" + std::to_string(i) + "].Color", m_lightColors[i]);
        }
        m_pShader->setVec3("viewPos", m_camera->getPosition());
        // create one large cube that acts as the floor
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0));
        model = glm::scale(model, glm::vec3(12.5f, 0.5f, 12.5f));
        m_pShader->setMat4("model", model);
        renderCube();
        // then create multiple cubes as the scenery
        glBindTexture(GL_TEXTURE_2D, m_containerTexture);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
        model = glm::scale(model, glm::vec3(0.5f));
        m_pShader->setMat4("model", model);
        renderCube();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
        model = glm::scale(model, glm::vec3(0.5f));
        m_pShader->setMat4("model", model);
        renderCube();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, -1.0f, 2.0));
        model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
        m_pShader->setMat4("model", model);
        renderCube();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 2.7f, 4.0));
        model = glm::rotate(model, glm::radians(23.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
        model = glm::scale(model, glm::vec3(1.25));
        m_pShader->setMat4("model", model);
        renderCube();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-2.0f, 1.0f, -3.0));
        model = glm::rotate(model, glm::radians(124.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
        m_pShader->setMat4("model", model);
        renderCube();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0));
        model = glm::scale(model, glm::vec3(0.5f));
        m_pShader->setMat4("model", model);
        renderCube();

        // finally show all the light sources as bright cubes
        if(m_pShaderLight)
        {
            m_pShaderLight->use();
            m_pShaderLight->setMat4("projection", projection);
            m_pShaderLight->setMat4("view", view);

            for (unsigned int i = 0; i < m_lightPositions.size(); i++)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(m_lightPositions[i]));
                model = glm::scale(model, glm::vec3(0.25f));
                m_pShaderLight->setMat4("model", model);
                m_pShaderLight->setVec3("lightColor", m_lightColors[i]);
                renderCube();
            }
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 2. blur bright fragments with two-pass Gaussian Blur
    // --------------------------------------------------
    bool horizontal = true, first_iteration = true;
    unsigned int amount = 10;
    if(m_pShaderBlur)
    {
        m_pShaderBlur->use();
        for (unsigned int i = 0; i < amount; i++)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, m_pingpongFBO[horizontal]);
            m_pShaderBlur->setInt("horizontal", horizontal);
            glBindTexture(GL_TEXTURE_2D, first_iteration ? m_colorBuffers[1] : m_pingpongColorbuffers[!horizontal]);  // bind texture of other framebuffer (or scene if first iteration)
            renderQuad();
            horizontal = !horizontal;
            if (first_iteration)
                first_iteration = false;
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 3. now render floating point color buffer to 2D quad and tonemap HDR colors to default framebuffer's (clamped) color range
    // --------------------------------------------------------------------------------------------------------------------------
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, m_width, m_height);
    if(m_pShaderBloomFinal)
    {
        m_pShaderBloomFinal->use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_colorBuffers[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_pingpongColorbuffers[!horizontal]);
        m_pShaderBloomFinal->setInt("bloom", bloom);
        m_pShaderBloomFinal->setFloat("exposure", exposure);
        renderQuad();
    }
}

void BloomScene::destroy() {
    if (m_pShader)
    {
        delete m_pShader;
        m_pShader = nullptr;
    }
    if (m_pShaderLight)
    {
        delete m_pShaderLight;
        m_pShaderLight = nullptr;
    }
    if (m_pShaderBlur)
    {
        delete m_pShaderBlur;
        m_pShaderBlur = nullptr;
    }
    if (m_pShaderBloomFinal)
    {
        delete m_pShaderBloomFinal;
        m_pShaderBloomFinal = nullptr;
    }
    if (m_cubeVAO != 0)
    {
        glDeleteVertexArrays(1, &m_cubeVAO);
        m_cubeVAO = 0;
    }
    if (m_quadVAO != 0)
    {
        glDeleteVertexArrays(1, &m_quadVAO);
        m_quadVAO = 0;
    }
    glDeleteFramebuffers(1, &m_hdrFBO);
    glDeleteTextures(2, m_colorBuffers);
    glDeleteRenderbuffers(1, &m_rboDepth);
    glDeleteFramebuffers(2, m_pingpongFBO);
    glDeleteTextures(2, m_pingpongColorbuffers);
    delete m_camera;
}

BloomScene::~BloomScene() {
}

std::map<std::string, std::any> BloomScene::propertyEvent(std::map<std::string, std::any> &map) {
    auto eventIdIt = map.find("event_id");
    if (eventIdIt != map.end() && eventIdIt->second.type() == typeid(std::string)) {
        auto eventIdStr = std::any_cast<std::string>(eventIdIt->second);
        if ("target_camera_touching_event" == eventIdStr) {
            parseTargetCameraEvent(map);
        }
    }
    return {};
}

void BloomScene::parseTargetCameraEvent(std::map<std::string, std::any> &event) {
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

void BloomScene::renderQuad() {
    if (m_quadVAO == 0)
    {
        float quadVertices[] = {
                // positions        // texture Coords
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Bottom Left
                 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
                -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, // Top Left
                 1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // Top Right
        };
        // setup plane VAO
        glGenVertexArrays(1, &m_quadVAO);
        glGenBuffers(1, &m_quadVBO);
        glBindVertexArray(m_quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(m_quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void BloomScene::renderCube() {
    // initialize (if necessary)
    if (m_cubeVAO == 0)
    {
        float vertices[] = {
                // back face (CCW viewed from back, so CW from front)
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
                -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
                -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
                -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
                -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
                -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
                // right face
                 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
                 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right
                 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
                 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
                 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left
                 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
                // bottom face
                -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
                 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
                 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
                 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
                -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
                -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
                // top face
                -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
                 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right
                 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
                 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
                -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f, // bottom-left
                -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f  // top-left
        };
        glGenVertexArrays(1, &m_cubeVAO);
        glGenBuffers(1, &m_cubeVBO);
        // fill buffer
        glBindBuffer(GL_ARRAY_BUFFER, m_cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // link vertex attributes
        glBindVertexArray(m_cubeVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    // render Cube
    glBindVertexArray(m_cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
