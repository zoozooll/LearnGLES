#include "BlendingScene.h"

#include <GLES3/gl32.h>
#include <map>

#include "Camera.h"
#include "TargetCamera.h"
#include "Shader.h"
#include "Texture.h"

BlendingScene::BlendingScene() {
    m_windows = {
            glm::vec3(-1.5f, 0.0f, -0.48f),
            glm::vec3( 1.5f, 0.0f, 0.51f),
            glm::vec3( 0.0f, 0.0f, 0.7f),
            glm::vec3(-0.3f, 0.0f, -2.3f),
            glm::vec3( 0.5f, 0.0f, -0.6f)
    };
}

void BlendingScene::init() {
    m_camera = new TargetCamera;
    // configure global opengl state
    // -----------------------------
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // build and compile our shader zprogram
    // ------------------------------------
    m_pShader = new Shader("shaders/blending/blending.vert", "shaders/blending/blending.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float cubeVertices[] = {
        // back face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
        // front face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
        // left face
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
        // right face
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
        // bottom face
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
        // top face
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left
    };
    float planeVertices[] = {
        // positions          // texture Coords
        5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,

        5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        5.0f, -0.5f, -5.0f,  2.0f, 2.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f
    };
    float transparentVertices[] = {
        // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
        -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.0f,  1.0f,  1.0f,

        -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.0f,  1.0f,  0.0f
    };
    // cube VAO
    glGenVertexArrays(1, &m_cubeVAO);
    glGenBuffers(1, &m_cubeVBO);
    glBindVertexArray(m_cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    // plane VAO
    glGenVertexArrays(1, &m_planeVAO);
    glGenBuffers(1, &m_planeVBO);
    glBindVertexArray(m_planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    // transparent VAO
    glGenVertexArrays(1, &m_transparentVAO);
    glGenBuffers(1, &m_transparentVBO);
    glBindVertexArray(m_transparentVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_transparentVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);

    // load textures
    // -------------
    m_cubeTexture = loadTexture("textures/marble.jpg");
    m_floorTexture = loadTexture("textures/metal.png");
    m_transparentTexture = loadTexture("textures/window.png");

    // shader configuration
    // --------------------
    m_pShader->use();
    m_pShader->setInt("texture1", 0);
}

void BlendingScene::resize(int width, int height) {
    m_camera->setAspec((float) width / (float) height);
    glViewport(0, 0, width, height);
}

void BlendingScene::draw() {
    m_camera->update();

    if (blendOn) {
        LOGI(__FILE_NAME__, "blend properties %x, %x, %x", srcFactor, dstFactor, blendEquationMode);
        glEnable(GL_BLEND);
        glBlendFunc(srcFactor, dstFactor);
        glBlendEquation(blendEquationMode);
    } else {
        glDisable(GL_BLEND);
    }

    // sort the transparent windows before rendering
    // ---------------------------------------------
    std::map<float, glm::vec3> sorted;
    for (unsigned int i = 0; i < m_windows.size(); i++)
    {
        float distance = glm::length(m_camera->getPosition() - m_windows[i]);
        sorted[distance] = m_windows[i];
    }

    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw objects
    if(m_pShader)
    {
        m_pShader->use();
        glm::mat4 projection = m_camera->getProjectionMatrix();
        glm::mat4 view = m_camera->getViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        m_pShader->setMat4("projection", projection);
        m_pShader->setMat4("view", view);
        // cubes
        glBindVertexArray(m_cubeVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_cubeTexture);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        m_pShader->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        m_pShader->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // floor
        glBindVertexArray(m_planeVAO);
        glBindTexture(GL_TEXTURE_2D, m_floorTexture);
        model = glm::mat4(1.0f);
        m_pShader->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // windows (from furthest to nearest)
        glBindVertexArray(m_transparentVAO);
        glBindTexture(GL_TEXTURE_2D, m_transparentTexture);
        for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, it->second);
            m_pShader->setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    }
}

void BlendingScene::destroy() {
    glDeleteVertexArrays(1, &m_cubeVAO);
    glDeleteVertexArrays(1, &m_planeVAO);
    glDeleteVertexArrays(1, &m_transparentVAO);
    glDeleteBuffers(1, &m_cubeVBO);
    glDeleteBuffers(1, &m_planeVBO);
    glDeleteBuffers(1, &m_transparentVBO);
    if (m_pShader)
    {
        delete m_pShader;
        m_pShader = nullptr;
    }
    delete m_camera;
}

BlendingScene::~BlendingScene() {
}

std::map<std::string, std::any> BlendingScene::propertyEvent(std::map<std::string, std::any> &map) {
    auto eventIdIt = map.find("event_id");
    if (eventIdIt != map.end() && eventIdIt->second.type() == typeid(std::string)) {
        auto eventIdStr = std::any_cast<std::string>(eventIdIt->second);
        if ("target_camera_touching_event" == eventIdStr) {
            parseTargetCameraEvent(map);
        }
        if ("blend_on_event" == eventIdStr) {
            parseBlendOnEvent(map);
        }
        if ("src_factor_event" == eventIdStr) {
            parseSrcFactorEvent(map);
        }
        if ("dst_factor_event" == eventIdStr) {
            parseDstFactorEvent(map);
        }
        if ("blend_equation_event" == eventIdStr) {
            parseBlendEquationEvent(map);
        }
    }
    return {};
}

void BlendingScene::parseBlendOnEvent(std::map<std::string, std::any> &event) {
    if (auto it = event.find("on"); it != event.end()) {
        if (it->second.type() == typeid(bool)) {
            blendOn = std::any_cast<bool>(it->second);
        }
    }
}

void BlendingScene::parseSrcFactorEvent(std::map<std::string, std::any> &event) {
    if (auto it = event.find("factor"); it != event.end()) {
        if (it->second.type() == typeid(int)) {
            const auto& val = std::any_cast<int>(it->second);
            const GLenum factors[] = {
                GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR,
                GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
                GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR,
                GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA
            };
            if (val >= 0 && val < sizeof(factors)/sizeof(factors[0])) {
                srcFactor = factors[val];
            }
        }
    }
}

void BlendingScene::parseDstFactorEvent(std::map<std::string, std::any> &event) {
    if (auto it = event.find("factor"); it != event.end()) {
        if (it->second.type() == typeid(int)) {
            const auto& val = std::any_cast<int>(it->second);
            const GLenum factors[] = {
                GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR,
                GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
                GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR,
                GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA
            };
            if (val >= 0 && val < sizeof(factors)/sizeof(factors[0])) {
                dstFactor = factors[val];
            }
        }
    }
}

void BlendingScene::parseBlendEquationEvent(std::map<std::string, std::any> &event) {
    if (auto it = event.find("mode"); it != event.end()) {
        if (it->second.type() == typeid(int)) {
            const auto& val = std::any_cast<int>(it->second);
            const GLenum modes[] = {
                GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_MIN, GL_MAX
            };
            if (val >= 0 && val < sizeof(modes)/sizeof(modes[0])) {
                blendEquationMode = modes[val];
            }
        }
    }
}

void BlendingScene::parseTargetCameraEvent(std::map<std::string, std::any> &event) {
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
                targetCamera->onDoubleTouching(glm::vec2(val[0], val[1]),
                    glm::vec2(val[2], val[3]),
                        glm::vec2(val[4], val[5]),
                        glm::vec2(val[6], val[7]));
            }
        }
    }

    if (event.find("reset") != event.end()) {
        targetCamera->reset();
    }
}
