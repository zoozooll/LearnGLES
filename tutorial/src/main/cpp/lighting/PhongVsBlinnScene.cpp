#include "PhongVsBlinnScene.h"

#include "Shader.h"
#include "Camera.h"
#include "TargetCamera.h"
#include "Texture.h"

PhongVsBlinnScene::PhongVsBlinnScene() {
}

void PhongVsBlinnScene::init() {
    m_camera = new TargetCamera;
    // configure global opengl state
    // -----------------------------
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // build and compile our shader zprogram
    // ------------------------------------
    m_pShader = new Shader("shaders/phong_blinn/advanced_lighting.vert",
            "shaders/phong_blinn/advanced_lighting.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float planeVertices[] = {
            // positions            // normals         // texcoords
            10.0f, -0.5f, 10.0f, 0.0f, 1.0f, 0.0f, 10.0f, 0.0f,
            -10.0f, -0.5f, 10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            -10.0f, -0.5f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 10.0f,

            10.0f, -0.5f, 10.0f, 0.0f, 1.0f, 0.0f, 10.0f, 0.0f,
            -10.0f, -0.5f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 10.0f,
            10.0f, -0.5f, -10.0f, 0.0f, 1.0f, 0.0f, 10.0f, 10.0f
    };
    // plane VAO
    glGenVertexArrays(1, &m_planeVAO);
    glGenBuffers(1, &m_planeVBO);
    glBindVertexArray(m_planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glBindVertexArray(0);

    // load textures
    // -------------
    m_floorTexture = loadTexture("textures/wood.png");

    // shader configuration
    // --------------------
    m_pShader->use();
    m_pShader->setInt("texture1", 0);
}

void PhongVsBlinnScene::resize(int width, int height) {
    m_camera->setAspec((float) width / (float) height);
    glViewport(0, 0, width, height);
}

void PhongVsBlinnScene::draw() {
    m_camera->update();
    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw objects
    if (m_pShader) {
        m_pShader->use();
        glm::mat4 projection = m_camera->getProjectionMatrix();
        glm::mat4 view = m_camera->getViewMatrix();
        m_pShader->setMat4("projection", projection);
        m_pShader->setMat4("view", view);
        // set light uniforms
        m_pShader->setVec3("viewPos", m_camera->getPosition());
        m_pShader->setVec3("lightPos", m_lightPos);
        m_pShader->setInt("blinn", blinn);
        // floor
        glBindVertexArray(m_planeVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_floorTexture);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}

void PhongVsBlinnScene::destroy() {
    glDeleteVertexArrays(1, &m_planeVAO);
    glDeleteBuffers(1, &m_planeVBO);
    if (m_pShader) {
        delete m_pShader;
        m_pShader = nullptr;
    }
    delete m_camera;
}

PhongVsBlinnScene::~PhongVsBlinnScene() {

}

std::map<std::string, std::any> PhongVsBlinnScene::propertyEvent(std::map<std::string, std::any> &map) {
    auto eventIdIt = map.find("event_id");
    if (eventIdIt != map.end() && eventIdIt->second.type() == typeid(std::string)) {
        auto eventIdStr = std::any_cast<std::string>(eventIdIt->second);
        if ("target_camera_touching_event" == eventIdStr) {
            parseTargetCameraEvent(map);
        }
        if ("blinn_on_event" == eventIdStr) {
            parseBlinnOnEvent(map);
        }
    }
    return {};
}

void PhongVsBlinnScene::parseBlinnOnEvent(std::map<std::string, std::any> &event) {
    if (auto it = event.find("on"); it != event.end()) {
        if (it->second.type() == typeid(bool)) {
            blinn = std::any_cast<bool>(it->second);
        }
    }
}

void PhongVsBlinnScene::parseTargetCameraEvent(std::map<std::string, std::any> &event) {
    auto *targetCamera = dynamic_cast<TargetCamera *>(m_camera);
    if (!targetCamera) return;

    if (auto it = event.find("single_touching"); it != event.end()) {
        if (it->second.type() == typeid(std::vector<float>)) {
            const auto &val = std::any_cast<const std::vector<float> &>(it->second);
            if (val.size() >= 4) {
                targetCamera->onSingleTouching(glm::vec2(val[0], val[1]), glm::vec2(val[2], val[3]));
            }
        }
    }

    if (auto it = event.find("double_touching"); it != event.end()) {
        if (it->second.type() == typeid(std::vector<float>)) {
            const auto &val = std::any_cast<const std::vector<float> &>(it->second);
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

bool PhongVsBlinnScene::isBlinn() const {
    return blinn;
}

void PhongVsBlinnScene::setBlinn(bool blinn) {
    PhongVsBlinnScene::blinn = blinn;
}
