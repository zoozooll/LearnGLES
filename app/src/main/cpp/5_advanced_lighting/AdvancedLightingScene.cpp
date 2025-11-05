//
// Created by Aaron Lee on 2023/08/07.
//

#include "AdvancedLightingScene.h"

#include <GLES3/gl32.h>
#include <stb_image.h>
#include <glm/ext.hpp>

#include "Shader.h"
#include "logutil.h"
#include "glerror.h"
#include "Texture.h"

bool blinn = false;
bool blinnKeyPressed = false;

void AdvancedLightingScene::init() {
// configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // build and compile shaders
    // -------------------------
    shader = new Shader("5/1.advanced_lighting.vert", "5/1.advanced_lighting.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float planeVertices[] = {
            // positions            // normals         // texcoords
            10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
            -10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
            -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

            10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
            -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
            10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
    };
    // plane VAO

    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindVertexArray(0);

    // load textures
    // -------------
    floorTexture = loadTexture("textures/wood.png");

    // shader configuration
    // --------------------
    shader->use();
    shader->setInt("texture1", 0);
}

void AdvancedLightingScene::resize(int width, int height) {
    BaseScene::resize(width, height);
    glViewport(0, 0, width, height);
}

void AdvancedLightingScene::draw() {
    BaseScene::draw();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// draw objects
    shader->use();
    glm::mat4 projection = camera->getProjectionMatrix();;
    glm::mat4 view = camera->getViewMatrix();;;
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    // set light uniforms
    shader->setVec3("viewPos", camera->getPosition());
    shader->setVec3("lightPos", lightPos);
    shader->setInt("blinn", blinn);
    // floor
    glBindVertexArray(planeVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, floorTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    check_gl_error();
//    LOGI("AdvancedLightingScene", "Light Mode: %s", blinn ? "Blinn-Phong" : "Phong");
}

void AdvancedLightingScene::destroy() {
    delete shader;
    glDeleteTextures(1, &floorTexture);
    glDeleteVertexArrays(1, &planeVAO);
    glDeleteBuffers(1, &planeVBO);
}
