//
// Created by zoozo on 7/25/2023.
//

#include "TransformationsExercise1Scene.h"

#include <GLES3/gl32.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Shader.h"
#include "stb_image.h"
#include "TimeUtil.h"

void TransformationsExercise1Scene::init() {
// build and compile our shader zprogram
    // ------------------------------------
    ourShader = new Shader("1/5.1.transform.vert", "1/5.1.transform.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            // positions          // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // load and create a texture
    // -------------------------

    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    unsigned char *file_data;
    size_t file_size;
    LoadDataFromAsset("textures/container.jpg", reinterpret_cast<void **>(&file_data), &file_size);
    unsigned char *data;
    int width, height, nrChannels;
    data = stbi_load_from_memory(file_data, file_size, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        LOGE("TexturesScene","Failed to load texture: textures/container.jpg");
    }
    stbi_image_free(data);
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    LoadDataFromAsset("textures/awesomeface.png", reinterpret_cast<void **>(&file_data), &file_size);
    data = stbi_load_from_memory(file_data, file_size, &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        LOGE("TexturesScene","Failed to load texture: textures/awesomeface.png");
    }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader->use();
    ourShader->setInt("texture1", 0);
    ourShader->setInt("texture2", 1);
}

void TransformationsExercise1Scene::resize(int width, int height) {
    glViewport(0, 0, width, height);
}

void TransformationsExercise1Scene::draw() {
// render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // create transformations
//    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
//    transform = glm::rotate(transform, (float)GetTimestampMilliSeconds() * 0.001f, glm::vec3(0.0f, 0.0f, 1.0f));

    // get matrix's uniform location and set matrix
    ourShader->use();
    unsigned int transformLoc = glGetUniformLocation(ourShader->ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

    // render container
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void TransformationsExercise1Scene::destroy() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void TransformationsExercise1Scene::move(const glm::vec2 &start_pivot, const glm::vec2 &end_pivot) {
    glm::mat4 l_matrix(1.0f);
    l_matrix = glm::translate(l_matrix, glm::vec3((end_pivot - start_pivot) * glm::vec2(0.001f, -0.001f), 0.f));
    transform = l_matrix * transform;
}

void TransformationsExercise1Scene::scale(const float &scale) {
    glm::mat4 l_matrix(1.0f);
    LOGI("TransformationsScene", "scale %f", scale);
    l_matrix = glm::scale(l_matrix, glm::vec3(scale, scale, scale));
    transform = l_matrix * transform;
}

void TransformationsExercise1Scene::yawPitch(const glm::vec2 &director) {

    glm::mat4 l_matrix(1.0f);
    glm::vec2 perpendicular = glm::normalize(glm::vec2(-director.y, director.x));
    auto angle = glm::length(director) * 0.1f / M_PI;
    l_matrix = glm::rotate(l_matrix, float(angle), glm::vec3(perpendicular, 0.f) );
    transform = l_matrix * transform;
}

void TransformationsExercise1Scene::roll(const float &angle) {
    LOGI("TransformationsScene", "roll %f", angle);
    glm::mat4 l_matrix(1.0f);
    l_matrix = glm::rotate(l_matrix, angle, glm::vec3(0.f, 0.f, 1.f));
    transform = l_matrix * transform;
}