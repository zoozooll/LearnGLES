#include "GeometryShaderScene.h"

#include <GLES3/gl32.h>

#include "Shader.h"
#include "Camera.h"
#include "TargetCamera.h"

GeometryShaderScene::GeometryShaderScene() {

}

void GeometryShaderScene::init() {
    m_camera = new TargetCamera;
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    m_pShader = new Shader("shaders/geometry_shader/9.1.geometry_shader.vert",
            "shaders/geometry_shader/9.1.geometry_shader.frag",
            "shaders/geometry_shader/9.1.geometry_shader.geom");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float points[] = {
            -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
            0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top-right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
            -0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // bottom-left
    };
    glGenBuffers(1, &m_VBO);
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);
}

void GeometryShaderScene::resize(int width, int height) {
    m_camera->setAspec((float) width / (float) height);
    glViewport(0, 0, width, height);
}

void GeometryShaderScene::draw() {
    m_camera->update();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw points
    if(m_pShader)
    {
        m_pShader->use();
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_POINTS, 0, 4);
    }
}

void GeometryShaderScene::destroy() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    if (m_pShader)
    {
        delete m_pShader;
        m_pShader = nullptr;
    }
    delete m_camera;
}

GeometryShaderScene::~GeometryShaderScene() {

}

std::map<std::string, std::any> GeometryShaderScene::propertyEvent(std::map<std::string, std::any> &map) {
    auto eventIdIt = map.find("event_id");
    if (eventIdIt != map.end() && eventIdIt->second.type() == typeid(std::string)) {
        auto eventIdStr = std::any_cast<std::string>(eventIdIt->second);
        if ("target_camera_touching_event" == eventIdStr) {
            parseTargetCameraEvent(map);
        }
    }
    return {};
}

void GeometryShaderScene::parseTargetCameraEvent(std::map<std::string, std::any> &event) {
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
