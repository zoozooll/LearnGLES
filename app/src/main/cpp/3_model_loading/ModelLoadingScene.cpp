//
// Created by Aaron Lee on 2023/08/03.
//

#include "ModelLoadingScene.h"

#include <GLES3/gl32.h>
#include <stb_image.h>

#include <glm/ext.hpp>

#include "Shader.h"
#include "Model.h"
#include "glerror.h"

void ModelLoadingScene::init() {
    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    ourShader = new Shader("3/1.model_loading.vert", "3/1.model_loading.frag");
    check_gl_error();
    // load models
    // -----------
    ourModel = new Model("objects/backpack/backpack.obj");
    model = glm::mat4(1.0f);
    check_gl_error();
}

void ModelLoadingScene::resize(int width, int height) {
    BaseScene::resize(width, height);
    glViewport(0, 0, width, height);
}

void ModelLoadingScene::draw() {
    // render
    BaseScene::draw();
    // ------
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // don't forget to enable shader before setting uniforms
    ourShader->use();

    // view/projection transformations
    glm::mat4 projection = camera->getProjectionMatrix();
    glm::mat4 view = camera->getViewMatrix();
    ourShader->setMat4("projection", projection);
    check_gl_error();
    ourShader->setMat4("view", view);
    check_gl_error();
    // render the loaded model
//    glm::mat4 model = glm::mat4(1.0f);
//    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
//    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
    ourShader->setMat4("model", model);
    check_gl_error();
    ourModel->Draw(*ourShader);
    check_gl_error();
}

void ModelLoadingScene::destroy() {
    delete ourShader;
    delete ourModel;
}

