//
// Created by Aaron Lee on 2023/8/22.
//

#include "GeometryShaderNormalsScene.h"

#include <GLES3/gl32.h>
#include <glm/glm.hpp>


#include "Shader.h"
#include "Model.h"

void GeometryShaderNormalsScene::init() {


    // configure global opengl state
// -----------------------------
    glEnable(GL_DEPTH_TEST);

// build and compile shaders
// -------------------------
    shader = new Shader("4/9.3.default.vsh", "4/9.3.default.fsh");
    normalShader = new Shader("4/9.3.normal_visualization.vsh",
                        "4/9.3.normal_visualization.fsh",
                        "4/9.3.normal_visualization.gsh");

// load models
// -----------
    stbi_set_flip_vertically_on_load(true);
    backpack = new Model("objects/backpack/backpack.obj");
}

void GeometryShaderNormalsScene::resize(int width, int height) {
    BaseScene::resize(width, height);
    glViewport(0, 0, width, height);

}

void GeometryShaderNormalsScene::draw() {
    // render
    BaseScene::draw();
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // configure transformation matrices
    glm::mat4 projection = camera->getProjectionMatrix();;
    glm::mat4 view = camera->getViewMatrix();;;
    glm::mat4 model = glm::mat4(1.0f);
    shader->use();
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    shader->setMat4("model", model);

    // draw model as usual
    backpack->Draw(*shader);

    // then draw model with normal visualizing geometry shader
    normalShader->use();
    normalShader->setMat4("projection", projection);
    normalShader->setMat4("view", view);
    normalShader->setMat4("model", model);

    backpack->Draw(*normalShader);
}

void GeometryShaderNormalsScene::destroy() {
    delete camera;
    delete shader;
    delete normalShader;
    delete backpack;
}