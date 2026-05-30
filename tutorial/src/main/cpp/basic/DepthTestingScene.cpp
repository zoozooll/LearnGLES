//
// Created by zoozo on 2026/5/13.
//

#include "DepthTestingScene.h"

#include <GLES3/gl32.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "TargetCamera.h"
#include "glerror.h"

DepthTestingScene::DepthTestingScene() {
}

void DepthTestingScene::init() {
    // configure global opengl state
    // -----------------------------
    if (cullFace) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
    if (depthTest) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
    glDepthFunc(depthFunc);

    // build and compile our shader zprogram
    // ------------------------------------
    m_pShader = new Shader("shaders/depth_testing/depth_testing.vert",
            "shaders/depth_testing/show_texture.frag"
            );

    m_DepthShader = new Shader("shaders/depth_testing/depth_testing.vert",
            "shaders/depth_testing/depth_testing.frag"
    );

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float cubeVertices[] = {
        // positions          // texture Coords
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
        // (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode).
        // this will cause the floor texture to repeat)
        5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.f,  0.0f, 2.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,

        5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        5.0f, -0.5f, -5.0f,  2.0f, 2.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
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
    glBindVertexArray(0);
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
    glBindVertexArray(0);

    // load textures
    // -------------
    m_cubeTexture = loadTexture("textures/marble.jpg");
    m_floorTexture = loadTexture("textures/metal.png");

    // shader configuration
    // --------------------
    m_pShader->use();
    m_pShader->setInt("texture0", 0);

    check_gl_error();
    m_camera = new TargetCamera();
    m_camera->setNear(3.f);
    m_camera->setFar(10.f);
}

void DepthTestingScene::resize(int width, int height) {
    m_camera->setAspec((float) width / (float) height);
    glViewport(0, 0, width, height);
}

void DepthTestingScene::draw() {
    m_camera->update();
    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto curShader = showDepth ? m_DepthShader : m_pShader;
    curShader->use();
    glm::mat4 model = glm::mat4(1.0f);
    curShader->setMat4("view", m_camera->getViewMatrix());
    curShader->setMat4("projection", m_camera->getProjectionMatrix());
    // cubes
    glBindVertexArray(m_cubeVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_cubeTexture);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
    curShader->setMat4("model", model);
    curShader->setTexture("texture0", m_cubeTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    check_gl_error();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
    curShader->setMat4("model", model);
    curShader->setTexture("texture0", m_cubeTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    check_gl_error();

    // floor
    glBindVertexArray(m_planeVAO);
    glBindTexture(GL_TEXTURE_2D, m_floorTexture);
    curShader->setMat4("model", glm::mat4(1.0f));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    curShader->setTexture("texture0", m_floorTexture);
    glBindVertexArray(0);
    check_gl_error();
}

void DepthTestingScene::destroy() {
    glDeleteVertexArrays(1, &m_cubeVAO);
    glDeleteVertexArrays(1, &m_planeVAO);
    glDeleteBuffers(1, &m_cubeVBO);
    glDeleteBuffers(1, &m_planeVBO);
    if (m_pShader)
    {
        delete m_pShader;
        m_pShader = nullptr;
    }
    if (m_DepthShader)
    {
        delete m_DepthShader;
        m_DepthShader = nullptr;
    }
    delete m_camera;
    check_gl_error();
}

DepthTestingScene::~DepthTestingScene() {
}

std::map<std::string, std::any> DepthTestingScene::propertyEvent(std::map<std::string, std::any> &map) {
    auto eventIdIt = map.find("event_id");
    if (eventIdIt != map.end() && eventIdIt->second.type() == typeid(std::string)) {
        auto eventIdStr = std::any_cast<std::string>(eventIdIt->second);
        if ("target_camera_touching_event" == eventIdStr) {
            parseTargetCameraEvent(map);
        }
        if ("depthtest_event" == eventIdStr) {
            parseDepthtestEvent(map);
        }
        if ("depthtest_func_event" == eventIdStr) {
            parseDepthFuncEvent(map);
        }
        if ("cullface_event" == eventIdStr) {
            parseCullFaceEvent(map);
        }
        if ("show_depth_event" == eventIdStr) {
            parseShowDepthEvent(map);
        }
    }
    return {};
}

void DepthTestingScene::parseTargetCameraEvent(std::map<std::string, std::any> &event) {
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

bool DepthTestingScene::isCullFace() const {
    return cullFace;
}

void DepthTestingScene::setCullFace(bool cullFace) {
    DepthTestingScene::cullFace = cullFace;
}

bool DepthTestingScene::isDepthTest() const {
    return depthTest;
}

void DepthTestingScene::setDepthTest(bool depthTest) {
    DepthTestingScene::depthTest = depthTest;
}

bool DepthTestingScene::isShowDepth() const {
    return showDepth;
}

void DepthTestingScene::setShowDepth(bool showDepth) {
    DepthTestingScene::showDepth = showDepth;
}

GLenum DepthTestingScene::getDepthFunc() const {
    return depthFunc;
}

void DepthTestingScene::setDepthFunc(GLenum depthFunc) {
    if (depthFunc >= GL_NEVER && depthFunc <= GL_ALWAYS) {
        DepthTestingScene::depthFunc = depthFunc;
    }
}

void DepthTestingScene::parseDepthtestEvent(std::map<std::string, std::any> &event) {
    if (auto it = event.find("on"); it != event.end()) {
        if (it->second.type() == typeid(bool)) {
            const auto& val = std::any_cast<bool>(it->second);
            if (val) {
                depthTest = true;
                glEnable(GL_DEPTH_TEST);
            } else {
                depthTest = false;
                glDisable(GL_DEPTH_TEST);
            }
        }
    }
}

void DepthTestingScene::parseDepthFuncEvent(std::map<std::string, std::any> &event) {
    if (auto it = event.find("func"); it != event.end()) {
        if (it->second.type() == typeid(int)) {
            const auto& val = std::any_cast<int>(it->second);
            depthFunc = GL_NEVER + val;
            glDepthFunc(depthFunc);
        }
    }
}

void DepthTestingScene::parseCullFaceEvent(std::map<std::string, std::any> &event) {
    if (auto it = event.find("on"); it != event.end()) {
        if (it->second.type() == typeid(bool)) {
            const auto& val = std::any_cast<bool>(it->second);
            if (val) {
                cullFace = true;
                glEnable(GL_CULL_FACE);
            } else {
                cullFace = false;
                glDisable(GL_CULL_FACE);
            }
        }
    }
}

void DepthTestingScene::parseShowDepthEvent(std::map<std::string, std::any> &event) {
    if (auto it = event.find("on"); it != event.end()) {
        if (it->second.type() == typeid(bool)) {
            showDepth = std::any_cast<bool>(it->second);
        }
    }
}
