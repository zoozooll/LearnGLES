#include "AsteroidScene.h"

#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "TimeUtil.h"

AsteroidScene::AsteroidScene() {
}

void AsteroidScene::init() {
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    m_pAsteroidShader = new Shader("asterioid/10.3.asteroids.vs", "asterioid/10.3.asteroids.fs");
    m_pPlanetShader = new Shader("asterioid/10.3.planet.vs", "asterioid/10.3.planet.fs");

    // load models
    // -----------
    m_pRockModel = new Model("models/rock/rock.obj");
    m_pPlanetModel = new Model("models/planet/planet.obj");

    // generate a large list of semi-random model transformation matrices
    // ------------------------------------------------------------------
    glm::mat4* modelMatrices = new glm::mat4[m_amount];
    srand(static_cast<unsigned int>(GetEscapeSecs())); // initialize random seed
    float radius = 150.0;
    float offset = 25.0f;
    for (unsigned int i = 0; i < m_amount; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
        float angle = (float)i / (float)m_amount * 360.0f;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));

        // 2. scale: Scale between 0.05 and 0.25f
        float scale = static_cast<float>((rand() % 20) / 100.0 + 0.05);
        model = glm::scale(model, glm::vec3(scale));

        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        float rotAngle = static_cast<float>((rand() % 360));
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

        // 4. now add to list of matrices
        modelMatrices[i] = model;
    }

    // configure instanced array
    // -------------------------
    glGenBuffers(1, &m_instanceBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

    // set transformation matrices as an instance vertex attribute (with divisor 1)
    if(m_pRockModel)
    {
        for (unsigned int i = 0; i < m_pRockModel->meshes.size(); i++)
        {
            unsigned int VAO = m_pRockModel->meshes[i].VAO;
            glBindVertexArray(VAO);
            // set attribute pointers for matrix (4 times vec4)
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
            glEnableVertexAttribArray(5);
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
            glEnableVertexAttribArray(6);
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

            glVertexAttribDivisor(3, 1);
            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);
            glVertexAttribDivisor(6, 1);

            glBindVertexArray(0);
        }
    }
    delete[] modelMatrices;
}

void AsteroidScene::resize(int width, int height) {
    glViewport(0, 0, width, height);
}

void AsteroidScene::draw() {
    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // configure transformation matrices
    glm::mat4 projection = m_camera->getProjectionMatrix();
    glm::mat4 view = m_camera->getViewMatrix();

    if(m_pPlanetShader && m_pPlanetModel)
    {
        m_pPlanetShader->use();
        m_pPlanetShader->setMat4("projection", projection);
        m_pPlanetShader->setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
        model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
        m_pPlanetShader->setMat4("model", model);
        m_pPlanetModel->Draw(*m_pPlanetShader);
    }

    if(m_pAsteroidShader && m_pRockModel)
    {
        m_pAsteroidShader->use();
        m_pAsteroidShader->setMat4("projection", projection);
        m_pAsteroidShader->setMat4("view", view);
        m_pAsteroidShader->setInt("texture_diffuse1", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_pRockModel->textures_loaded[0].id);
        for (unsigned int i = 0; i < m_pRockModel->meshes.size(); i++)
        {
            glBindVertexArray(m_pRockModel->meshes[i].VAO);
            glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(m_pRockModel->meshes[i].indices.size()), GL_UNSIGNED_INT, 0, m_amount);
            glBindVertexArray(0);
        }
    }
}

void AsteroidScene::destroy() {
    if (m_pAsteroidShader)
    {
        delete m_pAsteroidShader;
        m_pAsteroidShader = nullptr;
    }
    if (m_pPlanetShader)
    {
        delete m_pPlanetShader;
        m_pPlanetShader = nullptr;
    }
    if (m_pRockModel)
    {
        delete m_pRockModel;
        m_pRockModel = nullptr;
    }
    if (m_pPlanetModel)
    {
        delete m_pPlanetModel;
        m_pPlanetModel = nullptr;
    }
    glDeleteBuffers(1, &m_instanceBuffer);
    delete m_camera;
}

AsteroidScene::~AsteroidScene() {

}
