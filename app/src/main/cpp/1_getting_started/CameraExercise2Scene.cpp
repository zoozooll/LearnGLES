//
// Created by Aaron Lee on 2023/10/19.
//

#include "CameraExercise2Scene.h"

#include <GLES3/gl32.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <stb_image.h>
#include "Shader.h"
#include "Texture.h"

static int SCR_WIDTH = 0, SCR_HEIGHT = 0;

void CameraExercise2Scene::init() {
// configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // build and compile our shader zprogram
    // ------------------------------------
    ourShader = new Shader("1/billboard.vert", "1/billboard.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            // positions         // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f,  0.5f, 0.0f,   0.0f, 1.0f,  // top left

            0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   0.0f, 1.0f,  // top left
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBO);

    // load and create a texture
    // -------------------------

    // texture 1
    texture1 = loadTexture("textures/container.jpg");

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader->use();
    ourShader->setInt("texture1", 0);

    camera.setRadius(3.f);
    camera.setLongitude(-90.f);
}

void CameraExercise2Scene::resize(int width, int height) {
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

void CameraExercise2Scene::draw() {
    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    // activate shader
    ourShader->use();

    // pass projection matrix to shader (note that in this case it could change every frame)
    glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    ourShader->setMat4("projection", projection);

    // camera/view transformation
    glm::mat4 view = camera.GetViewMatrix();
    ourShader->setMat4("view", view);

    // render boxes
    glBindVertexArray(VAO);

    // calculate the model matrix for each object and pass it to shader before drawing
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    vec3 billboardFrontWorld = vec3(0.f, 0.f, 1.f);
    vec3 billboardPosition = vec3(0.f);
    vec3 billboard_to_camera = glm::normalize(camera.getPosition() - billboardPosition);
    vec3 pivot = glm::normalize(cross(billboardFrontWorld, billboard_to_camera));
    float theta = acos(dot(billboardFrontWorld, billboard_to_camera));
    rotate(model, theta, pivot);
    ourShader->setMat4("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 6);

}

void CameraExercise2Scene::destroy() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteTextures(1, &texture1);
}


void CameraExercise2Scene::yawPitch(const glm::vec2 &director) {

}

void CameraExercise2Scene::onDoubleClick(const glm::vec2 point) {

}
