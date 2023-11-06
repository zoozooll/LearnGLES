//
// Created by zoozo on 8/9/2023.
//

#include "CoordinateSystemDepthScene.h"

#include <GLES3/gl32.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Shader.h"
#include "logutil.h"
#include "TimeUtil.h"

static int SCR_WIDTH = 0;
static int SCR_HEIGHT = 0;

void CoordinateSystemDepthScene::init() {
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    ourShader = new Shader("1/6.2.coordinate_systems.vert", "1/6.2.coordinate_systems.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    unsigned int VBO;
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
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
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
        LOGE("CoordinateSystemScene","Failed to load texture : %s", "textures/container.jpg");
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
        LOGE("CoordinateSystemScene","Failed to load texture : %s", "textures/awesomeface.png");
    }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader->use();
    ourShader->setInt("texture1", 0);
    ourShader->setInt("texture2", 1);
}

void CoordinateSystemDepthScene::resize(int width, int height) {
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

void CoordinateSystemDepthScene::draw() {
    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // activate shader
    ourShader->use();

    // create transformations
//    glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 view          = glm::mat4(1.0f);
    glm::mat4 projection    = glm::mat4(1.0f);
    view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    // retrieve the matrix uniform locations
    unsigned int modelLoc = glGetUniformLocation(ourShader->ID, "model");
    unsigned int viewLoc  = glGetUniformLocation(ourShader->ID, "view");
    // pass them to the shaders (3 different ways)
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    ourShader->setMat4("projection", projection);
    ourShader->setVec2("screenSize", (float)SCR_WIDTH, (float)SCR_HEIGHT);

    // render box
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CoordinateSystemDepthScene::destroy() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteTextures(1, &texture1);
    glDeleteTextures(1, &texture2);
    delete ourShader;
}

void CoordinateSystemDepthScene::move(const glm::vec2 &start_pivot, const glm::vec2 &end_pivot) {
    glm::mat4 l_matrix(1.0f);
    l_matrix = glm::translate(l_matrix, glm::vec3((end_pivot - start_pivot) * glm::vec2(0.001f, -0.001f), 0.f));
    model = l_matrix * model;
}

void CoordinateSystemDepthScene::scale(const float &scale) {
    glm::mat4 l_matrix(1.0f);
    LOGI("TransformationsScene", "scale %f", scale);
    l_matrix = glm::scale(l_matrix, glm::vec3(scale, scale, scale));
    model = l_matrix * model;
}

void CoordinateSystemDepthScene::yawPitch(const glm::vec2 &director) {

    glm::mat4 l_matrix(1.0f);
    glm::vec2 perpendicular = glm::normalize(glm::vec2(-director.y, director.x));
    auto angle = glm::length(director) * 0.1f / M_PI;
    l_matrix = glm::rotate(l_matrix, float(angle), glm::vec3(perpendicular, 0.f) );
    model = l_matrix * model;
}

void CoordinateSystemDepthScene::roll(const float &angle) {
    LOGI("TransformationsScene", "roll %f", angle);
    glm::mat4 l_matrix(1.0f);
    l_matrix = glm::rotate(l_matrix, angle, glm::vec3(0.f, 0.f, 1.f));
    model = l_matrix * model;
}