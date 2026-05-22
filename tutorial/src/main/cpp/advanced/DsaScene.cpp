#include "DsaScene.h"

#include "GLES3/gl32.h"
#include "logutil.h"

const char* vertexShaderSource = R"(#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
})";
const char* fragmentShaderSource = R"(#version 330 core
out vec4 FragColor;
void main()
{
   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

DsaScene::DsaScene() {

}

void DsaScene::init() {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        LOGW(__FILE_NAME__, "ERROR::SHADER::VERTEX::COMPILATION_FAILED %s", infoLog);
    }
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        LOGW(__FILE_NAME__, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED %s", infoLog);
    }
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
        LOGW(__FILE_NAME__, "ERROR::SHADER::PROGRAM::LINKING_FAILED %s", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
            0.5f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
    };
    // Not supported in GLES
//    glCreateBuffers(1, &m_vbo);
//    glNamedBufferStorage(m_vbo, sizeof(vertices), vertices, 0x0);
//
//    unsigned int indices[] = {
//            0, 1, 3,
//            1, 2, 3
//    };
//    glCreateBuffers(1, &m_ebo);
//    glNamedBufferStorage(m_ebo, sizeof(indices), nullptr, GL_DYNAMIC_STORAGE_BIT);
//    glNamedBufferSubData(m_ebo, 0, sizeof(indices), indices);
//
//    glCreateVertexArrays(1, &m_vao);
//    glEnableVertexArrayAttrib(m_vao, 0);
//    glVertexArrayAttribFormat(m_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
//    glVertexArrayAttribBinding(m_vao, 0, 0);
//    glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, sizeof(float) * 3);
//    glVertexArrayElementBuffer(m_vao, m_ebo);
}

void DsaScene::resize(int width, int height) {
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

void DsaScene::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(m_shaderProgram);
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void DsaScene::destroy() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    glDeleteProgram(m_shaderProgram);
}

DsaScene::~DsaScene() {

}
