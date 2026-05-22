#include "SkeletalAnimationScene.h"

#include <stb_image.h>

#include "Shader.h"
#include "Camera.h"
#include "AnimatedModel.h"
#include "Animation.h"
#include "Animator.h"
#include "TimeUtil.h"

SkeletalAnimationScene::SkeletalAnimationScene() {
}

void SkeletalAnimationScene::init() {
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
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

void SkeletalAnimationScene::draw() {
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
