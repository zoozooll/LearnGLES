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

static int SCR_WIDTH;
static int SCR_HEIGHT;

void ModelLoadingScene::init() {
    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    ourShader = new Shader("3/1.model_loading.vert", "3/1.model_loading.frag");

    // load models
    // -----------
    ourModel = new Model("objects/backpack/backpack.obj");
    model = glm::mat4(1.0f);
}

void ModelLoadingScene::resize(int width, int height) {
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

void ModelLoadingScene::draw() {
    // render
    // ------
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // don't forget to enable shader before setting uniforms
    ourShader->use();

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
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

void ModelLoadingScene::move(const glm::vec2 &start_pivot, const glm::vec2 &end_pivot) {
    glm::mat4 l_matrix(1.0f);
    l_matrix = glm::translate(l_matrix, glm::vec3((end_pivot - start_pivot) * glm::vec2(0.001f, -0.001f), 0.f));
    model = l_matrix * model;
}

void ModelLoadingScene::scale(const float &scale) {
    glm::mat4 l_matrix(1.0f);
    LOGI(__FILE_NAME__, "scale %f", scale);
    l_matrix = glm::scale(l_matrix, glm::vec3(scale, scale, scale));
    model = l_matrix * model;
}

void ModelLoadingScene::yawPitch(const glm::vec2 &director) {

    glm::mat4 l_matrix(1.0f);
    glm::vec2 perpendicular = glm::normalize(glm::vec2(-director.y, director.x));
    auto angle = glm::length(director) * 0.1f / M_PI;
    l_matrix = glm::rotate(l_matrix, float(angle), glm::vec3(perpendicular, 0.f) );
    model = l_matrix * model;
}

void ModelLoadingScene::roll(const float &angle) {
    LOGI(__FILE_NAME__, "roll %f", angle);
    glm::mat4 l_matrix(1.0f);
    l_matrix = glm::rotate(l_matrix, angle, glm::vec3(0.f, 0.f, 1.f));
    model = l_matrix * model;
}

