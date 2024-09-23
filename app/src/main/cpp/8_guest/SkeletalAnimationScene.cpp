//
// Created by Aaron Lee on 2023/8/22.
//

#include "SkeletalAnimationScene.h"

#include <GLES3/gl32.h>

#include "Camera.h"
#include "Shader.h"
#include "AnimatedModel.h"
#include "Animation.h"
#include "Animator.h"
#include "TimeUtil.h"

void SkeletalAnimationScene::init() {
    camera = new Camera({0.F, 0.F, 3.F});

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    ourShader = new Shader("8/anim_model.vs", "8/anim_model.fs");

    // load models
    // -----------
    ourModel = new AnimatedModel("objects/vampire/dancing_vampire.dae");
    Animation danceAnimation("objects/vampire/dancing_vampire.dae", ourModel);
    animator = new Animator(&danceAnimation);

    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void SkeletalAnimationScene::resize(int width, int height) {
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

void SkeletalAnimationScene::draw() {
    // per-frame time logic
    // --------------------
    float currentFrame = GetEscapeSecs();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // input
    // -----
    animator->UpdateAnimation(deltaTime);

    // render
    // ------
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // don't forget to enable shader before setting uniforms
    ourShader->use();

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera->GetViewMatrix();
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

void SkeletalAnimationScene::destroy() {
    delete camera;
    delete ourShader;
    delete ourModel;
    delete animator;
}