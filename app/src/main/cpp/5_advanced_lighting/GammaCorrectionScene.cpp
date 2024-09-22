//
// Created by Aaron Lee on 2023/8/22.
//

#include "GammaCorrectionScene.h"

#include <GLES3/gl32.h>

#include "Shader.h"
#include "Camera.h"
#include "Texture.h"

void GammaCorrectionScene::init() {
    camera = new Camera({0.F, 0.F, 3.F});
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // build and compile shaders
    // -------------------------
    shader = new Shader("5/2.gamma_correction.vsh", "5/2.gamma_correction.fsh");

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
    floorTexture               = loadTexture("resources/textures/wood.png", false);
    floorTextureGammaCorrected = loadTexture("resources/textures/wood.png", true);

    // shader configuration
    // --------------------
    shader->use();
    shader->setInt("floorTexture", 0);
}

void GammaCorrectionScene::resize(int width, int height) {
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

void GammaCorrectionScene::draw() {
    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw objects
    shader->use();
    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera->GetViewMatrix();
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    // set light uniforms
    glUniform3fv(glGetUniformLocation(shader->ID, "lightPositions"), 4, &lightPositions[0][0]);
    glUniform3fv(glGetUniformLocation(shader->ID, "lightColors"), 4, &lightColors[0][0]);
    shader->setVec3("viewPos", camera->Position);
    shader->setInt("gamma", gammaEnabled);
    // floor
    glBindVertexArray(planeVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gammaEnabled ? floorTextureGammaCorrected : floorTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void GammaCorrectionScene::destroy() {
    glDeleteVertexArrays(1, &planeVAO);
    glDeleteBuffers(1, &planeVBO);
    delete camera;
    delete shader;
}

void GammaCorrectionScene::setGammaEnabled(bool gammaEnabled) {
    GammaCorrectionScene::gammaEnabled = gammaEnabled;
}
