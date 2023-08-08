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
    ourShader = new Shader("1.model_loading.vert", "1.model_loading.frag");

    // load models
    // -----------
    ourModel = new Model("objects/backpack/backpack.obj");
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
    ourShader->setMat4("view", view);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
    ourShader->setMat4("model", model);
    ourModel->Draw(*ourShader);
    check_gl_error();
}

void ModelLoadingScene::destroy() {
    delete ourShader;
    delete ourModel;
}
