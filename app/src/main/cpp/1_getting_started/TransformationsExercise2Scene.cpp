//
// Created by zoozo on 7/25/2023.
//

#include "TransformationsExercise2Scene.h"

#include <GLES3/gl32.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Shader.h"
#include "stb_image.h"
#include "TimeUtil.h"
#include "glm/gtx/matrix_decompose.hpp"
#include "constants.h"

using glm::vec3;
using glm::vec4;
using glm::quat;
using glm::mat4;

void TransformationsExercise2Scene::init() {
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

void TransformationsExercise2Scene::resize(int width, int height) {
    glViewport(0, 0, width, height);
}

void TransformationsExercise2Scene::draw() {
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

void TransformationsExercise2Scene::destroy() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

std::map<std::string, std::any>
TransformationsExercise2Scene::sendCommand(std::map<std::string, std::any> commands) {
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

void TransformationsExercise2Scene::translate(glm::vec3 t) {
    vec3 l_scale;
    quat l_rotation;
    vec3 translation;
    vec3 skew;
    vec4 perspective;
    glm::decompose(transform, l_scale, l_rotation, translation, skew, perspective);
    mat4 mat_scale = glm::scale(mat4(1.f), l_scale);
    mat4 mat_rotate = glm::mat4_cast(l_rotation);
    mat4 mat_translate = glm::translate(mat4(1.f), t);
    transform = mat_translate * mat_rotate * mat_scale;
}

void TransformationsExercise2Scene::rotate(glm::vec3 r) {
    vec3 l_scale;
    quat l_rotation;
    vec3 translation;
    vec3 skew;
    vec4 perspective;
    glm::decompose(transform, l_scale, l_rotation, translation, skew, perspective);
    mat4 mat_scale = glm::scale(mat4(1.f), l_scale);

    mat4 QuatAroundX = glm::rotate(mat4(1.f), r.x, X_AXIS);
    mat4 QuatAroundY = glm::rotate(mat4(1.f), r.y, Y_AXIS);
    mat4 QuatAroundZ = glm::rotate(mat4(1.f), r.z, Z_AXIS);
    mat4 mat_rotate = QuatAroundX * QuatAroundY * QuatAroundZ;
    mat4 mat_translate = glm::translate(mat4(1.f), translation);
    transform = mat_translate * mat_rotate * mat_scale;
}

void TransformationsExercise2Scene::scale(glm::vec3 s) {
    vec3 l_scale;
    quat l_rotation;
    vec3 translation;
    vec3 skew;
    vec4 perspective;
    glm::decompose(transform, l_scale, l_rotation, translation, skew, perspective);
    mat4 mat_scale = glm::scale(mat4(1.f), s);
    mat4 mat_rotate = glm::mat4_cast(l_rotation);
    mat4 mat_translate = glm::translate(mat4(1.f), translation);
    transform = mat_translate * mat_rotate * mat_scale;
}

void TransformationsExercise2Scene::translateX(float t) {
    vec3 l_scale;
    quat l_rotation;
    vec3 translation;
    vec3 skew;
    vec4 perspective;
    glm::decompose(transform, l_scale, l_rotation, translation, skew, perspective);
    mat4 mat_scale = glm::scale(mat4(1.f), l_scale);
    mat4 mat_rotate = glm::mat4_cast(l_rotation);
    translation.x = t;
    mat4 mat_translate = glm::translate(mat4(1.f), translation);
    transform = mat_translate * mat_rotate * mat_scale;
}

void TransformationsExercise2Scene::translateY(float t) {
    vec3 l_scale;
    quat l_rotation;
    vec3 translation;
    vec3 skew;
    vec4 perspective;
    glm::decompose(transform, l_scale, l_rotation, translation, skew, perspective);
    mat4 mat_scale = glm::scale(mat4(1.f), l_scale);
    mat4 mat_rotate = glm::mat4_cast(l_rotation);
    translation.y = t;
    mat4 mat_translate = glm::translate(mat4(1.f), translation);
    transform = mat_translate * mat_rotate * mat_scale;
}

void TransformationsExercise2Scene::translateZ(float t) {
    vec3 l_scale;
    quat l_rotation;
    vec3 translation;
    vec3 skew;
    vec4 perspective;
    glm::decompose(transform, l_scale, l_rotation, translation, skew, perspective);
    mat4 mat_scale = glm::scale(mat4(1.f), l_scale);
    mat4 mat_rotate = glm::mat4_cast(l_rotation);
    translation.z = t;
    mat4 mat_translate = glm::translate(mat4(1.f), translation);
    transform = mat_translate * mat_rotate * mat_scale;
}

void TransformationsExercise2Scene::rotateX(float d) {
    vec3 l_scale;
    quat l_rotation;
    vec3 translation;
    vec3 skew;
    vec4 perspective;
    glm::decompose(transform, l_scale, l_rotation, translation, skew, perspective);
    mat4 mat_scale = glm::scale(mat4(1.f), l_scale);

    float r = glm::radians(d);
    auto euler = glm::eulerAngles(l_rotation);
    euler.x = r;

    mat4 QuatAroundX = glm::rotate(mat4(1.f), euler.x, X_AXIS);
    mat4 QuatAroundY = glm::rotate(mat4(1.f), euler.y, Y_AXIS);
    mat4 QuatAroundZ = glm::rotate(mat4(1.f), euler.z, Z_AXIS);
    mat4 mat_rotate = QuatAroundX * QuatAroundY * QuatAroundZ;
    mat4 mat_translate = glm::translate(mat4(1.f), translation);
    transform = mat_translate * mat_rotate * mat_scale;
}

void TransformationsExercise2Scene::rotateY(float d) {
    vec3 l_scale;
    quat l_rotation;
    vec3 translation;
    vec3 skew;
    vec4 perspective;
    glm::decompose(transform, l_scale, l_rotation, translation, skew, perspective);
    mat4 mat_scale = glm::scale(mat4(1.f), l_scale);

    float r = glm::radians(d);
    auto euler = glm::eulerAngles(l_rotation);
    euler.y = r;

    mat4 QuatAroundX = glm::rotate(mat4(1.f), euler.x, X_AXIS);
    mat4 QuatAroundY = glm::rotate(mat4(1.f), euler.y, Y_AXIS);
    mat4 QuatAroundZ = glm::rotate(mat4(1.f), euler.z, Z_AXIS);
    mat4 mat_rotate = QuatAroundX * QuatAroundY * QuatAroundZ;
    mat4 mat_translate = glm::translate(mat4(1.f), translation);
    transform = mat_translate * mat_rotate * mat_scale;
}

void TransformationsExercise2Scene::rotateZ(float d) {
    vec3 l_scale;
    quat l_rotation;
    vec3 translation;
    vec3 skew;
    vec4 perspective;
    glm::decompose(transform, l_scale, l_rotation, translation, skew, perspective);
    mat4 mat_scale = glm::scale(mat4(1.f), l_scale);
    float r = glm::radians(d);
    auto euler = glm::eulerAngles(l_rotation);
    euler.z = r;

    mat4 QuatAroundX = glm::rotate(mat4(1.f), euler.x, X_AXIS);
    mat4 QuatAroundY = glm::rotate(mat4(1.f), euler.y, Y_AXIS);
    mat4 QuatAroundZ = glm::rotate(mat4(1.f), euler.z, Z_AXIS);
    mat4 mat_rotate = QuatAroundX * QuatAroundY * QuatAroundZ;
    mat4 mat_translate = glm::translate(mat4(1.f), translation);
    transform = mat_translate * mat_rotate * mat_scale;
}

void TransformationsExercise2Scene::scaleX(float s) {
    vec3 l_scale;
    quat l_rotation;
    vec3 translation;
    vec3 skew;
    vec4 perspective;
    glm::decompose(transform, l_scale, l_rotation, translation, skew, perspective);
    l_scale.x = s;
    mat4 mat_scale = glm::scale(mat4(1.f), l_scale);
    mat4 mat_rotate = glm::mat4_cast(l_rotation);
    mat4 mat_translate = glm::translate(mat4(1.f), translation);
    transform = mat_translate * mat_rotate * mat_scale;
}

void TransformationsExercise2Scene::scaleY(float s) {
    vec3 l_scale;
    quat l_rotation;
    vec3 translation;
    vec3 skew;
    vec4 perspective;
    glm::decompose(transform, l_scale, l_rotation, translation, skew, perspective);
    l_scale.y = s;
    mat4 mat_scale = glm::scale(mat4(1.f), l_scale);
    mat4 mat_rotate = glm::mat4_cast(l_rotation);
    mat4 mat_translate = glm::translate(mat4(1.f), translation);
    transform = mat_translate * mat_rotate * mat_scale;
}

void TransformationsExercise2Scene::scaleZ(float s) {
    vec3 l_scale;
    quat l_rotation;
    vec3 translation;
    vec3 skew;
    vec4 perspective;
    glm::decompose(transform, l_scale, l_rotation, translation, skew, perspective);
    l_scale.z = s;
    mat4 mat_scale = glm::scale(mat4(1.f), l_scale);
    mat4 mat_rotate = glm::mat4_cast(l_rotation);
    mat4 mat_translate = glm::translate(mat4(1.f), translation);
    transform = mat_translate * mat_rotate * mat_scale;
}
