#include "SkeletalAnimationScene.h"

#include <stb_image.h>

#include "Shader.h"
#include "Camera.h"
#include "TargetCamera.h"
#include "AnimatedModel.h"
#include "Animation.h"
#include "Animator.h"
#include "TimeUtil.h"

SkeletalAnimationScene::SkeletalAnimationScene() {
}

void SkeletalAnimationScene::init() {
    m_camera = new TargetCamera;
// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    ourShader = new Shader("shaders/skeletal_anim/anim_model.vert", "shaders/skeletal_anim/anim_model.frag");

    // load models
    // -----------
    ourModel = new AnimatedModel("objects/vampire/dancing_vampire.dae");
    danceAnimation = new Animation(("objects/vampire/dancing_vampire.dae"), ourModel);
    animator = new Animator(danceAnimation);
}

void SkeletalAnimationScene::resize(int width, int height) {
    m_camera->setAspec((float) width / (float) height);
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

void SkeletalAnimationScene::draw() {
    m_camera->update();
    // per-frame time logic
    // --------------------
    float currentFrame = static_cast<float>(GetEscapeSecs());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (animator)
        animator->UpdateAnimation(deltaTime);

    // render
    // ------
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (ourShader && ourModel && animator)
    {
        // don't forget to enable shader before setting uniforms
        ourShader->use();

        // view/projection transformations
        glm::mat4 projection = m_camera->getProjectionMatrix();
        glm::mat4 view = m_camera->getViewMatrix();
        ourShader->setMat4("projection", projection);
        ourShader->setMat4("view", view);

        auto transforms = animator->GetFinalBoneMatrices();
        for (int i = 0; i < transforms.size(); ++i)
            ourShader->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.4f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(.5f, .5f, .5f));	// it's a bit too big for our scene, so scale it down
        ourShader->setMat4("model", model);
        ourModel->Draw(*ourShader);
    }
}

void SkeletalAnimationScene::destroy() {
    if (ourShader) delete ourShader;
    if (ourModel) delete ourModel;
    if (danceAnimation) delete danceAnimation;
    if (animator) delete animator;
    if (m_camera) delete m_camera;
}

SkeletalAnimationScene::~SkeletalAnimationScene() {

}

std::map<std::string, std::any> SkeletalAnimationScene::propertyEvent(std::map<std::string, std::any> &map) {
    auto eventIdIt = map.find("event_id");
    if (eventIdIt != map.end() && eventIdIt->second.type() == typeid(std::string)) {
        auto eventIdStr = std::any_cast<std::string>(eventIdIt->second);
        if ("target_camera_touching_event" == eventIdStr) {
            parseTargetCameraEvent(map);
        }
    }
    return {};
}

void SkeletalAnimationScene::parseTargetCameraEvent(std::map<std::string, std::any> &event) {
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
