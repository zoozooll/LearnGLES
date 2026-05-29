#include "ParallaxMappingScene.h"

#include "Shader.h"
#include "Camera.h"
#include "TargetCamera.h"
#include "Texture.h"
#include "TimeUtil.h"

ParallaxMappingScene::ParallaxMappingScene() {
}

void ParallaxMappingScene::init() {
    camera = new TargetCamera;
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    m_pShader = new Shader("shaders/parallax_mapping/5.1.parallax_mapping.vert",
            "shaders/parallax_mapping/5.1.parallax_mapping.frag");

    // load textures
    // -------------
    m_diffuseMap = loadTexture("textures/bricks2.jpg");
    m_normalMap  = loadTexture("textures/bricks2_normal.jpg");
    m_heightMap  = loadTexture("textures/bricks2_disp.jpg");

    // shader configuration
    // --------------------
    m_pShader->use();
    m_pShader->setInt("diffuseMap", 0);
    m_pShader->setInt("normalMap", 1);
    m_pShader->setInt("depthMap", 2);
}

void ParallaxMappingScene::resize(int width, int height) {
    camera->setAspec((float) width / (float) height);
    glViewport(0, 0, width, height);
}

void ParallaxMappingScene::draw() {
    camera->update();
    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // configure view/projection matrices
    if(m_pShader)
    {
        glm::mat4 projection = camera->getProjectionMatrix();
        glm::mat4 view = camera->getViewMatrix();
        m_pShader->use();
        m_pShader->setMat4("projection", projection);
        m_pShader->setMat4("view", view);
        // render parallax-mapped quad
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(GetEscapeSecs() * -10.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0))); // rotate the quad to show parallax mapping from multiple directions
        m_pShader->setMat4("model", model);
        m_pShader->setVec3("viewPos", camera->getPosition());
        m_pShader->setVec3("lightPos", m_lightPos);
        m_pShader->setFloat("heightScale", heightScale); // adjust with Q and E keys
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_diffuseMap);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_normalMap);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, m_heightMap);
        renderQuad();

        // render light source (simply re-renders a smaller plane at the light's position for debugging/visualization)
        model = glm::mat4(1.0f);
        model = glm::translate(model, m_lightPos);
        model = glm::scale(model, glm::vec3(0.1f));
        m_pShader->setMat4("model", model);
        renderQuad();
    }
}

void ParallaxMappingScene::destroy() {
    glDeleteVertexArrays(1, &m_quadVAO);
    glDeleteBuffers(1, &m_quadVBO);
    if (m_pShader)
    {
        delete m_pShader;
        m_pShader = nullptr;
    }
    delete camera;
}

ParallaxMappingScene::~ParallaxMappingScene() {

}

std::map<std::string, std::any> ParallaxMappingScene::propertyEvent(std::map<std::string, std::any> &map) {
    auto eventIdIt = map.find("event_id");
    if (eventIdIt != map.end() && eventIdIt->second.type() == typeid(std::string)) {
        auto eventIdStr = std::any_cast<std::string>(eventIdIt->second);
        if ("target_camera_touching_event" == eventIdStr) {
            parseTargetCameraEvent(map);
        }
    }
    return {};
}

void ParallaxMappingScene::parseTargetCameraEvent(std::map<std::string, std::any> &event) {
    auto* targetCamera = dynamic_cast<TargetCamera*>(camera);
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

void ParallaxMappingScene::renderQuad() {

}
