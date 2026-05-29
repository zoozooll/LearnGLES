#include "GammaCorrectionScene.h"

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "TargetCamera.h"

GammaCorrectionScene::GammaCorrectionScene() {
}

void GammaCorrectionScene::init() {
    m_camera = new TargetCamera;
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // build and compile shaders
    // -------------------------
    m_pShader = new Shader("shaders/gamma_correction/2.gamma_correction.vert",
            "shaders/gamma_correction/2.gamma_correction.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float planeVertices[] = {
            // positions            // normals         // texcoords
            10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
            -10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
            -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

            10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
            -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
            10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
    };
    // plane VAO
    glGenVertexArrays(1, &m_planeVAO);
    glGenBuffers(1, &m_planeVBO);
    glBindVertexArray(m_planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_planeVBO);
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
    m_floorTexture               = loadTexture("textures/wood.png", false);
    m_floorTextureGammaCorrected = loadTexture("textures/wood.png", true);

    // shader configuration
    // --------------------
    m_pShader->use();
    m_pShader->setInt("floorTexture", 0);

    // lighting info
    // -------------
    m_lightPositions[0] = glm::vec3(-3.0f, 0.0f, 0.0f);
    m_lightPositions[1] = glm::vec3(-1.0f, 0.0f, 0.0f);
    m_lightPositions[2] = glm::vec3 (1.0f, 0.0f, 0.0f);
    m_lightPositions[3] = glm::vec3 (3.0f, 0.0f, 0.0f);

    m_lightColors[0] = glm::vec3(0.25);
    m_lightColors[1] = glm::vec3(0.50);
    m_lightColors[2] = glm::vec3(0.75);
    m_lightColors[3] = glm::vec3(1.00);
}

void GammaCorrectionScene::resize(int width, int height) {
    m_camera->setAspec((float) width / (float) height);
    glViewport(0, 0, width, height);
}

void GammaCorrectionScene::draw() {
    m_camera->update();
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
        m_pShader->setMat4("projection", projection);
        m_pShader->setMat4("view", view);
        // set light uniforms
        glUniform3fv(glGetUniformLocation(m_pShader->ID, "lightPositions"), 4, &m_lightPositions[0][0]);
        glUniform3fv(glGetUniformLocation(m_pShader->ID, "lightColors"), 4, &m_lightColors[0][0]);
        m_pShader->setVec3("viewPos", m_camera->getPosition());
        m_pShader->setInt("gamma", gammaEnabled);
        // floor
        glBindVertexArray(m_planeVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gammaEnabled ? m_floorTextureGammaCorrected : m_floorTexture);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}

void GammaCorrectionScene::destroy() {
    glDeleteVertexArrays(1, &m_planeVAO);
    glDeleteBuffers(1, &m_planeVBO);
    if (m_pShader)
    {
        delete m_pShader;
        m_pShader = nullptr;
    }
    delete m_camera;
}

GammaCorrectionScene::~GammaCorrectionScene() {

}

std::map<std::string, std::any> GammaCorrectionScene::propertyEvent(std::map<std::string, std::any> &map) {
    auto eventIdIt = map.find("event_id");
    if (eventIdIt != map.end() && eventIdIt->second.type() == typeid(std::string)) {
        auto eventIdStr = std::any_cast<std::string>(eventIdIt->second);
        if ("target_camera_touching_event" == eventIdStr) {
            parseTargetCameraEvent(map);
        }
    }
    return {};
}

void GammaCorrectionScene::parseTargetCameraEvent(std::map<std::string, std::any> &event) {
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

bool GammaCorrectionScene::isGammaEnabled() const {
    return gammaEnabled;
}

void GammaCorrectionScene::setGammaEnabled(bool gammaEnabled) {
    GammaCorrectionScene::gammaEnabled = gammaEnabled;
}
