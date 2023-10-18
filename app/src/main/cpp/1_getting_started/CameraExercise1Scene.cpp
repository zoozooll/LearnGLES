//
// Created by huion on 2023/10/18.
//

#include "CameraExercise1Scene.h"

#include <GLES3/gl32.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <stb_image.h>
#include "Shader.h"
#include "Texture.h"

// world space positions of our cubes
static glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
};

static int SCR_WIDTH = 0, SCR_HEIGHT = 0;

void CameraExercise1Scene::init() {
// configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    ourShader = new Shader("1/6.3.coordinate_systems.vert", "1/6.3.coordinate_systems.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            // positions          // colors           // texture coords
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


    // load and create a texture
    // -------------------------

    // texture 1
    texture1 = loadTexture("textures/container.jpg");

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader->use();
    ourShader->setInt("texture1", 0);
}

void CameraExercise1Scene::resize(int width, int height) {
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

void CameraExercise1Scene::draw() {
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
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    ourShader->setMat4("projection", projection);

    // camera/view transformation
    glm::mat4 view = camera.GetViewMatrix();
    ourShader->setMat4("view", view);

    // render boxes
    glBindVertexArray(VAO);

        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        ourShader->setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 6);

}

void CameraExercise1Scene::destroy() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteTextures(1, &texture1);
}

void CameraExercise1Scene::move(const glm::vec2 &start_pivot, const glm::vec2 &end_pivot) {
    camera.ProcessMove(glm::vec3((end_pivot - start_pivot) * glm::vec2(0.001f, -0.001f), 0.f));
}

void CameraExercise1Scene::scale(const float &scale) {
    float zoom = 0.f;
    if (scale > 1.02f) {
        zoom = 1.f;
    } else if (scale < 0.98f) {
        zoom = -1.f;
    }
    camera.ProcessMouseScroll(zoom);
}

void CameraExercise1Scene::yawPitch(const glm::vec2 &director) {
    camera.ProcessMouseMovement(director.x, director.y);
}

void CameraExercise1Scene::roll(const float &angle) {
}

void CameraExercise1Scene::onDoubleClick(const glm::vec2 point) {
//    camera.Position = glm::vec3(0.0f, 0.0f, 3.0f);
//    camera.WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
//    camera.Yaw = YAW;
//    camera.Pitch = PITCH;
//    camera.Zoom = ZOOM;
}
