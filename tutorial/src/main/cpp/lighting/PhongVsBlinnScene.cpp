#include "PhongVsBlinnScene.h"

#include "Shader.h"
#include "Camera.h"
#include "Texture.h"

PhongVsBlinnScene::PhongVsBlinnScene() {
}

void PhongVsBlinnScene::init() {
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // build and compile our shader zprogram
    // ------------------------------------
    m_pShader = new Shader("shaders/phong_blinn/1.advanced_lighting.vs",
            "shaders/phong_blinn/1.advanced_lighting.fs");

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
    // plane VAO
    glGenVertexArrays(1, &m_planeVAO);
    glGenBuffers(1, &m_planeVBO);
    glBindVertexArray(m_planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_planeVBO);
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
    m_floorTexture = loadTexture("textures/wood.png");

    // shader configuration
    // --------------------
    m_pShader->use();
    m_pShader->setInt("texture1", 0);
}

void PhongVsBlinnScene::resize(int width, int height) {
    glViewport(0, 0, width, height);
}

void PhongVsBlinnScene::draw() {
    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw objects
    if(m_pShader)
    {
        m_pShader->use();
        glm::mat4 projection = m_camera->getProjectionMatrix();
        glm::mat4 view = m_camera->getViewMatrix();
        m_pShader->setMat4("projection", projection);
        m_pShader->setMat4("view", view);
        // set light uniforms
        m_pShader->setVec3("viewPos", m_camera->getPosition());
        m_pShader->setVec3("lightPos", m_lightPos);
        m_pShader->setInt("blinn", blinn);
        // floor
        glBindVertexArray(m_planeVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_floorTexture);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}

void PhongVsBlinnScene::destroy() {
    glDeleteVertexArrays(1, &m_planeVAO);
    glDeleteBuffers(1, &m_planeVBO);
    if (m_pShader)
    {
        delete m_pShader;
        m_pShader = nullptr;
    }
    delete m_camera;
}

PhongVsBlinnScene::~PhongVsBlinnScene() {

}

bool PhongVsBlinnScene::isBlinn() const {
    return blinn;
}

void PhongVsBlinnScene::setBlinn(bool blinn) {
    PhongVsBlinnScene::blinn = blinn;
}
