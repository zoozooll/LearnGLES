#include "ParallaxMappingScene.h"

#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "TimeUtil.h"

ParallaxMappingScene::ParallaxMappingScene() {
}

void ParallaxMappingScene::init() {
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    m_pShader = new Shader("shaders/parallax_mapping/5.1.parallax_mapping.vert",
            "shaders/parallax_mapping/5.1.parallax_mapping.frag");

    // load textures
    // -------------
    m_diffuseMap = loadTexture("textures/bricks2.jpg");
    m_normalMap  = loadTexture("textures/bricks2_normal.jpg");
    m_heightMap  = loadTexture("textures/bricks2_disp.jpg");

    // shader configuration
    // --------------------
    m_pShader->use();
    m_pShader->setInt("diffuseMap", 0);
    m_pShader->setInt("normalMap", 1);
    m_pShader->setInt("depthMap", 2);
}

void ParallaxMappingScene::resize(int width, int height) {
    glViewport(0, 0, width, height);
}

void ParallaxMappingScene::draw() {
    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // configure view/projection matrices
    if(m_pShader)
    {
        glm::mat4 projection = camera->getProjectionMatrix();
        glm::mat4 view = camera->getViewMatrix();
        m_pShader->use();
        m_pShader->setMat4("projection", projection);
        m_pShader->setMat4("view", view);
        // render parallax-mapped quad
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(GetEscapeSecs() * -10.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0))); // rotate the quad to show parallax mapping from multiple directions
        m_pShader->setMat4("model", model);
        m_pShader->setVec3("viewPos", camera->getPosition());
        m_pShader->setVec3("lightPos", m_lightPos);
        m_pShader->setFloat("heightScale", heightScale); // adjust with Q and E keys
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_diffuseMap);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_normalMap);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, m_heightMap);
        renderQuad();

        // render light source (simply re-renders a smaller plane at the light's position for debugging/visualization)
        model = glm::mat4(1.0f);
        model = glm::translate(model, m_lightPos);
        model = glm::scale(model, glm::vec3(0.1f));
        m_pShader->setMat4("model", model);
        renderQuad();
    }
}

void ParallaxMappingScene::destroy() {
    glDeleteVertexArrays(1, &m_quadVAO);
    glDeleteBuffers(1, &m_quadVBO);
    if (m_pShader)
    {
        delete m_pShader;
        m_pShader = nullptr;
    }
    delete camera;
}

ParallaxMappingScene::~ParallaxMappingScene() {

}

void ParallaxMappingScene::renderQuad() {

}
