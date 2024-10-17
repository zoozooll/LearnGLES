//
// Created by Aaron Lee on 2023/8/22.
//

#include "GeometryShaderExplodingScene.h"

#include <GLES3/gl32.h>
#include <glm/glm.hpp>


#include "Shader.h"
#include "Model.h"

void GeometryShaderExplodingScene::init() {

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    shader = new Shader("4/9.2.geometry_shader->vsh", "4/9.2.geometry_shader->fsh", "4/9.2.geometry_shader->gsh");

    // load models
    // -----------
    nanosuit = new Model("objects/nanosuit/nanosuit.obj");
}

void GeometryShaderExplodingScene::resize(int width, int height) {
    BaseScene::resize(width, height);
    glViewport(0, 0, width, height);

}

void GeometryShaderExplodingScene::draw() {
    // render
    BaseScene::draw();
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // configure transformation matrices
    glm::mat4 projection = camera->getProjectionMatrix();
    glm::mat4 view = camera->getViewMatrix();;;
    glm::mat4 model = glm::mat4(1.0f);
    shader->use();
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    shader->setMat4("model", model);

    // add time component to geometry shader in the form of a uniform
    shader->setFloat("time", time);

    // draw model
    nanosuit->Draw(*shader);
}

void GeometryShaderExplodingScene::destroy() {
    delete camera;
    delete shader;
}

void GeometryShaderExplodingScene::setTime(float time) {
    GeometryShaderExplodingScene::time = time;
}
