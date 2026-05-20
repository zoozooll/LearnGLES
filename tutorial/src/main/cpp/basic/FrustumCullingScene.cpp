#include "FrustumCullingScene.h"

#include "Shader.h"
#include "Camera.h"
#include "entity.h"

FrustumCullingScene::FrustumCullingScene() {

}

void FrustumCullingScene::init() {
    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    ourShader = new Shader("1.model_loading.vs", "1.model_loading.fs");

    // load entities
    // -----------
    Model model("objects/planet/planet.obj");
    ourEntity = new Entity(model);
    ourEntity->transform.setLocalPosition({ 0, 0, 0 });
    const float scale = 1.0;
    ourEntity->transform.setLocalScale({ scale, scale, scale });

    {
        Entity* lastEntity = ourEntity;

        for (unsigned int x = 0; x < 20; ++x)
        {
            for (unsigned int z = 0; z < 20; ++z)
            {
                ourEntity->addChild(model);
                lastEntity = ourEntity->children.back().get();

                //Set transform values
                lastEntity->transform.setLocalPosition({ x * 10.f - 100.f,  0.f, z * 10.f - 100.f });
            }
        }
    }
    ourEntity->updateSelfAndChild();
}

void FrustumCullingScene::resize(int width, int height) {
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

void FrustumCullingScene::draw() {
    // render
    // ------
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (ourShader && ourEntity)
    {
        // don't forget to enable shader before setting uniforms
        ourShader->use();

        // view/projection transformations
        glm::mat4 projection = m_camera->getProjectionMatrix();
        const Frustum camFrustum = createFrustumFromCamera(*m_camera, (float)m_width / (float)m_height, glm::radians(m_camera->), 0.1f, 100.0f);

//        m_cameraSpy->ProcessMouseMovement(2, 0);
        glm::mat4 view = m_camera->getViewMatrix();

        ourShader->setMat4("projection", projection);
        ourShader->setMat4("view", view);

        // draw our scene graph
        unsigned int total = 0, display = 0;
        ourEntity->drawSelfAndChild(camFrustum, *ourShader, display, total);
        std::cout << "Total process in CPU : " << total << " / Total send to GPU : " << display << std::endl;

        ourEntity->updateSelfAndChild();
    }
}

void FrustumCullingScene::destroy() {
    if (ourShader) delete ourShader;
    if (ourEntity) delete ourEntity;
    if (m_camera) delete m_camera;
    if (m_cameraSpy) delete m_cameraSpy;
}

FrustumCullingScene::~FrustumCullingScene() {

}
