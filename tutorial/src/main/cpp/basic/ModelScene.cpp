#include "ModelScene.h"

#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "TargetCamera.h"

ModelScene::ModelScene() {
}

void ModelScene::init() {
    m_camera = new TargetCamera;
    // configure global opengl state
    // -----------------------------
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    m_pShader = new Shader("shaders/model/1.model_loading.vert", "shaders/model/1.model_loading.frag");

    // load models
    // -----------
    m_pModel = new Model("objects/backpack/backpack.obj");
}

void ModelScene::resize(int width, int height) {
    m_camera->setAspec((float) width / (float) height);
    glViewport(0, 0, width, height);
}

void ModelScene::draw() {
    m_camera->update();
    // render
    // ------
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // be sure to activate shader when setting uniforms/drawing objects
    if(m_pShader && m_pModel)
    {
        m_pShader->use();

        // view/projection transformations
        glm::mat4 projection = m_camera->getProjectionMatrix();
        glm::mat4 view = m_camera->getViewMatrix();
        m_pShader->setMat4("projection", projection);
        m_pShader->setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        m_pShader->setMat4("model", model);
        m_pModel->Draw(*m_pShader);
    }
}

void ModelScene::destroy() {
    if (m_pShader)
    {
        delete m_pShader;
        m_pShader = nullptr;
    }
    if (m_pModel)
    {
        delete m_pModel;
        m_pModel = nullptr;
    }
    delete m_camera;
}

ModelScene::~ModelScene() {

}

std::map<std::string, std::any> ModelScene::propertyEvent(std::map<std::string, std::any> &map) {
    auto eventIdIt = map.find("event_id");
    if (eventIdIt != map.end() && eventIdIt->second.type() == typeid(std::string)) {
        auto eventIdStr = std::any_cast<std::string>(eventIdIt->second);
        if ("target_camera_touching_event" == eventIdStr) {
            parseTargetCameraEvent(map);
        }
    }
    return {};
}

void ModelScene::parseTargetCameraEvent(std::map<std::string, std::any> &event) {
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
