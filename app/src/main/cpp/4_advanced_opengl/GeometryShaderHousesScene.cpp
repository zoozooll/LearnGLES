//
// Created by Aaron Lee on 2023/8/22.
//

#include "GeometryShaderHousesScene.h"

#include <GLES3/gl32.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Shader.h"

void GeometryShaderHousesScene::init() {
    camera = new Camera({0.F, 0.F, 3.F});

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    shader = new Shader("4/9.1.geometry_shader.vsh", "4/9.1.geometry_shader.fsh", "4/9.1.geometry_shader.gsh");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float points[] = {
            -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
            0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top-right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
            -0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // bottom-left
    };

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);
}

void GeometryShaderHousesScene::resize(int width, int height) {
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

void GeometryShaderHousesScene::draw() {
    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw points
    shader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, 4);
}

void GeometryShaderHousesScene::destroy() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}