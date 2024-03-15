//
// Created by zoozo on 8/9/2023.
//

#include "CoordinateSystemExercise3Scene.h"
#include <GLES3/gl32.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <glm/gtx/matrix_decompose.hpp>
#include "Shader.h"
#include "logutil.h"
#include "constants.h"
#include "glm/gtx/string_cast.hpp"

using glm::vec3;
using glm::vec4;
using glm::quat;
using glm::mat4;

static int SCR_WIDTH = 0;
static int SCR_HEIGHT = 0;

void CoordinateSystemExercise3Scene::init() {
// build and compile our shader zprogram
    // ------------------------------------
    ourShader = new Shader("1/6.1.coordinate_systems.vert", "1/6.1.coordinate_systems.frag");

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
    unsigned int VBO, EBO;
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

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

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
    LoadDataFromAsset("textures/arrow.png", reinterpret_cast<void **>(&file_data), &file_size);
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
        LOGE("CoordinateSystemScene","Failed to load texture : %s", "textures/arrow.png");
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
    LoadDataFromAsset("textures/arrow.png", reinterpret_cast<void **>(&file_data), &file_size);
    data = stbi_load_from_memory(file_data, file_size, &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        LOGE("CoordinateSystemScene","Failed to load texture : %s", "textures/arrow.png");
    }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader->use();
    ourShader->setInt("texture1", 0);
    ourShader->setInt("texture2", 1);
}

void CoordinateSystemExercise3Scene::resize(int width, int height) {
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

void CoordinateSystemExercise3Scene::draw() {
// render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

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
//    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    // retrieve the matrix uniform locations
    unsigned int modelLoc = glGetUniformLocation(ourShader->ID, "model");
    unsigned int viewLoc  = glGetUniformLocation(ourShader->ID, "view");
    // pass them to the shaders (3 different ways)
    vec3 right   (model[0][0], model[1][0], model[2][0]);
    vec3 up      (model[0][1], model[1][1], model[2][1]);
    vec3 forward (model[0][2], model[1][2], model[2][2]);

    vec3 l_x = glm::normalize(glm::mat3(model) * X_AXIS);
    vec3 l_y = glm::normalize(glm::mat3(model) * Y_AXIS);
    vec3 l_z = glm::normalize(glm::mat3(model) * Z_AXIS);
    LOGI(__FILE_NAME__, "update right: %s, up: %s, forward: %s", glm::to_string(right + l_x).c_str(),
         glm::to_string(up + l_y).c_str(), glm::to_string(forward + l_z).c_str());

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    ourShader->setMat4("projection", projection);

    // render container
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void CoordinateSystemExercise3Scene::destroy() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteTextures(1, &texture1);
    glDeleteTextures(1, &texture2);
    delete ourShader;
}

std::map<std::string, std::any>
CoordinateSystemExercise3Scene::sendCommand(std::map<std::string, std::any> commands) {
    for (const auto& [key, value]: commands) {
        if ("translate_x" == key && value.type() == typeid(float)) {
            auto l_value = any_cast<float>(value);
            translateX(l_value);
        } else if ("translate_y" == key && value.type() == typeid(float)) {
            auto l_value = any_cast<float>(value);
            translateY(l_value);
        } else if ("translate_z" == key && value.type() == typeid(float)) {
            auto l_value = any_cast<float>(value);
            translateZ(l_value);
        } else if ("rotate_x" == key && value.type() == typeid(float)) {
            auto l_value = any_cast<float>(value);
            rotateX(l_value);
        } else if ("rotate_y" == key && value.type() == typeid(float)) {
            auto l_value = any_cast<float>(value);
            rotateY(l_value);
        } else if ("rotate_z" == key && value.type() == typeid(float)) {
            auto l_value = any_cast<float>(value);
            rotateZ(l_value);
        } else if ("scale_x" == key && value.type() == typeid(float)) {
            auto l_value = any_cast<float>(value);
            scaleX(l_value);
        } else if ("scale_y" == key && value.type() == typeid(float)) {
            auto l_value = any_cast<float>(value);
            scaleY(l_value);
        } else if ("scale_z" == key && value.type() == typeid(float)) {
            auto l_value = any_cast<float>(value);
            scaleZ(l_value);
        }
    }
    return {};
}

void CoordinateSystemExercise3Scene::translate(glm::vec3 t) {

}

void CoordinateSystemExercise3Scene::rotate(glm::vec3 r) {

}

void CoordinateSystemExercise3Scene::scale(glm::vec3 s) {

}

void CoordinateSystemExercise3Scene::translateX(float t) {
    vec3 l_x = glm::normalize(glm::mat3(model) * X_AXIS);
    mat4 l_matrix = glm::translate(mat4(1.f), l_x * t * 0.01f);
    model = l_matrix * model;
}

void CoordinateSystemExercise3Scene::translateY(float t) {
    vec3 l_x = glm::normalize(glm::mat3(model) * Y_AXIS);
    mat4 l_matrix = glm::translate(mat4(1.f), l_x * t * 0.01f);
    model = l_matrix * model;
}

void CoordinateSystemExercise3Scene::translateZ(float t) {
    vec3 l_x = glm::normalize(glm::mat3(model) * Z_AXIS);
    mat4 l_matrix = glm::translate(mat4(1.f), l_x * t * 0.01f);
    model = l_matrix * model;
}

void CoordinateSystemExercise3Scene::rotateX(float d) {
    vec3 l_scale;
    quat l_rotation;
    vec3 translation;
    vec3 skew;
    vec4 perspective;
    glm::decompose(model, l_scale, l_rotation, translation, skew, perspective);
    mat4 mat_scale = glm::scale(mat4(1.f), l_scale);
    l_rotation = glm::rotate(l_rotation, glm::radians(d * 5.f), X_AXIS);
    mat4 mat_rotate = glm::mat4_cast(l_rotation);
    mat4 mat_translate = glm::translate(mat4(1.f), translation);
    model = mat_translate * mat_rotate * mat_scale;
}

void CoordinateSystemExercise3Scene::rotateY(float d) {
    vec3 l_scale;
    quat l_rotation;
    vec3 translation;
    vec3 skew;
    vec4 perspective;
    glm::decompose(model, l_scale, l_rotation, translation, skew, perspective);
    mat4 mat_scale = glm::scale(mat4(1.f), l_scale);
    l_rotation = glm::rotate(l_rotation, glm::radians(d * 5.f), Y_AXIS);
    mat4 mat_rotate = glm::mat4_cast(l_rotation);
    mat4 mat_translate = glm::translate(mat4(1.f), translation);
    model = mat_translate * mat_rotate * mat_scale;
}

void CoordinateSystemExercise3Scene::rotateZ(float d) {
    vec3 l_scale;
    quat l_rotation;
    vec3 translation;
    vec3 skew;
    vec4 perspective;
    glm::decompose(model, l_scale, l_rotation, translation, skew, perspective);
    mat4 mat_scale = glm::scale(mat4(1.f), l_scale);
    l_rotation = glm::rotate(l_rotation, glm::radians(d * 5.f), Z_AXIS);
    mat4 mat_rotate = glm::mat4_cast(l_rotation);
    mat4 mat_translate = glm::translate(mat4(1.f), translation);
    model = mat_translate * mat_rotate * mat_scale;
}

void CoordinateSystemExercise3Scene::scaleX(float s) {
    vec3 l_scale;
    quat l_rotation;
    vec3 translation;
    vec3 skew;
    vec4 perspective;
    glm::decompose(model, l_scale, l_rotation, translation, skew, perspective);
    float scale = 1.f + s * 0.1f;
    l_scale.x *= scale;
    mat4 mat_scale = glm::scale(mat4(1.f), l_scale);
    mat4 mat_rotate = glm::mat4_cast(l_rotation);
    mat4 mat_translate = glm::translate(mat4(1.f), translation);
    model = mat_translate * mat_rotate * mat_scale;
}

void CoordinateSystemExercise3Scene::scaleY(float s) {
    vec3 l_scale;
    quat l_rotation;
    vec3 translation;
    vec3 skew;
    vec4 perspective;
    glm::decompose(model, l_scale, l_rotation, translation, skew, perspective);
    float scale = 1.f + s * 0.1f;
    l_scale.y *= scale;
    mat4 mat_scale = glm::scale(mat4(1.f), l_scale);
    mat4 mat_rotate = glm::mat4_cast(l_rotation);
    mat4 mat_translate = glm::translate(mat4(1.f), translation);
    model = mat_translate * mat_rotate * mat_scale;
}

void CoordinateSystemExercise3Scene::scaleZ(float s) {
    vec3 l_scale;
    quat l_rotation;
    vec3 translation;
    vec3 skew;
    vec4 perspective;
    glm::decompose(model, l_scale, l_rotation, translation, skew, perspective);
    float scale = 1.f + s * 0.1f;
    l_scale.z *= scale;
    mat4 mat_scale = glm::scale(mat4(1.f), l_scale);
    mat4 mat_rotate = glm::mat4_cast(l_rotation);
    mat4 mat_translate = glm::translate(mat4(1.f), translation);
    model = mat_translate * mat_rotate * mat_scale;
}

void CoordinateSystemExercise3Scene::update() {
    mat4 l_matrix(1.f);
    model = l_matrix;
}

