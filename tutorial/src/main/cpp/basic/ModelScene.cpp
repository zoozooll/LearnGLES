#include "ModelScene.h"

#include "Shader.h"
#include "Model.h"
#include "Camera.h"

ModelScene::ModelScene() {
}

void ModelScene::init() {
    m_camera = new Camera;
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    m_pShader = new Shader("shaders/model/1.model_loading.vs", "shaders/model/1.model_loading.fs");

    // load models
    // -----------
    m_pModel = new Model("objects/backpack/backpack.obj");
}

void ModelScene::resize(int width, int height) {
    glViewport(0, 0, width, height);
}

void ModelScene::draw() {
    // render
    // ------
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // be sure to activate shader when setting uniforms/drawing objects
    if(m_pShader && m_pModel)
    {
        m_pShader->use();

        // view/projection transformations
        glm::mat4 projection = m_camera->getProjectionMatrix();
        glm::mat4 view = m_camera->getViewMatrix();
        m_pShader->setMat4("projection", projection);
        m_pShader->setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        m_pShader->setMat4("model", model);
        m_pModel->Draw(*m_pShader);
    }
}

void ModelScene::destroy() {
    if (m_pShader)
    {
        delete m_pShader;
        m_pShader = nullptr;
    }
    if (m_pModel)
    {
        delete m_pModel;
        m_pModel = nullptr;
    }
    delete m_camera;
}

ModelScene::~ModelScene() {

}
