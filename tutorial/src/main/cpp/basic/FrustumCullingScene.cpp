#include "FrustumCullingScene.h"

#include "Shader.h"
#include "Camera.h"
#include "TargetCamera.h"
#include "entity.h"

FrustumCullingScene::FrustumCullingScene() {

}

void FrustumCullingScene::init() {
    m_camera = new TargetCamera;
    m_camera->reset();
    m_cameraSpy = new TargetCamera;
    m_cameraSpy->reset();
    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    ourShader = new Shader("shaders/frustum_culling/model_loading.vert",
            "shaders/frustum_culling/model_loading.frag");

    // load entities
    // -----------
    m_model = std::make_unique<Model>("objects/planet/planet.obj");
    ourEntity = new Entity(*m_model);
    ourEntity->transform.setLocalPosition({ 0, 0, 0 });
    const float scale = 1.0;
    ourEntity->transform.setLocalScale({ scale, scale, scale });

    {
        Entity* lastEntity = ourEntity;

        for (unsigned int x = 0; x < 20; ++x)
        {
            for (unsigned int z = 0; z < 20; ++z)
            {
                ourEntity->addChild(*m_model);
                lastEntity = ourEntity->children.back().get();

                //Set transform values
                lastEntity->transform.setLocalPosition({ x * 10.f - 100.f,  0.f, z * 10.f - 100.f });
            }
        }
    }
    ourEntity->updateSelfAndChild();
}

void FrustumCullingScene::resize(int width, int height) {
    m_camera->setAspec((float) width / (float) height);
    m_cameraSpy->setAspec((float) width / (float) height);
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

void FrustumCullingScene::draw() {
    m_camera->update();
    m_cameraSpy->update();
    // render
    // ------
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (ourShader && ourEntity)
    {
        // don't forget to enable shader before setting uniforms
        ourShader->use();

        // view/projection transformations
        glm::mat4 projection = m_camera->getProjectionMatrix();
        const Frustum camFrustum = createFrustumFromCamera(*m_camera, (float)m_width / (float)m_height, glm::radians(m_camera->getVdy()), 0.1f, 100.0f);

//        m_cameraSpy->ProcessMouseMovement(2, 0);
        glm::mat4 view = m_camera->getViewMatrix();

        ourShader->setMat4("projection", projection);
        ourShader->setMat4("view", view);

        // draw our scene graph
        unsigned int total = 0, display = 0;
        ourEntity->drawSelfAndChild(camFrustum, *ourShader, display, total);
        LOGI("FrustumCullingScene", "Total process in CPU : %u / Total send to GPU : %u", total, display);

        ourEntity->updateSelfAndChild();
    }
}

void FrustumCullingScene::destroy() {
    if (ourShader) delete ourShader;
    if (ourEntity) delete ourEntity;
    if (m_camera) delete m_camera;
    if (m_cameraSpy) delete m_cameraSpy;
    m_model.reset();
}

FrustumCullingScene::~FrustumCullingScene() {

}

std::map<std::string, std::any> FrustumCullingScene::propertyEvent(std::map<std::string, std::any> &map) {
    auto eventIdIt = map.find("event_id");
    if (eventIdIt != map.end() && eventIdIt->second.type() == typeid(std::string)) {
        auto eventIdStr = std::any_cast<std::string>(eventIdIt->second);
        if ("target_camera_touching_event" == eventIdStr) {
            parseTargetCameraEvent(map);
        }
    }
    return {};
}

void FrustumCullingScene::parseTargetCameraEvent(std::map<std::string, std::any> &event) {
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
