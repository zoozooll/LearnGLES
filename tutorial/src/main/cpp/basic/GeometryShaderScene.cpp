#include "GeometryShaderScene.h"

#include <GLES3/gl32.h>

#include "Shader.h"
#include "Camera.h"

GeometryShaderScene::GeometryShaderScene() {

}

void GeometryShaderScene::init() {
    m_camera = new Camera;
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    m_pShader = new Shader("geometry_shader/9.1.geometry_shader.vs",
            "geometry_shader/9.1.geometry_shader.fs",
            "geometry_shader/9.1.geometry_shader.gs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float points[] = {
            -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
            0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top-right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
            -0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // bottom-left
    };
    glGenBuffers(1, &m_VBO);
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);
}

void GeometryShaderScene::resize(int width, int height) {
    glViewport(0, 0, width, height);
}

void GeometryShaderScene::draw() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw points
    if(m_pShader)
    {
        m_pShader->use();
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_POINTS, 0, 4);
    }
}

void GeometryShaderScene::destroy() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    if (m_pShader)
    {
        delete m_pShader;
        m_pShader = nullptr;
    }
    delete m_camera;
}

GeometryShaderScene::~GeometryShaderScene() {

}
