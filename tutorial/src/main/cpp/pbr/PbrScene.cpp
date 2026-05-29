#include "PbrScene.h"

#include "Shader.h"
#include "TargetCamera.h"
#include "Texture.h"
#include "TimeUtil.h"

PbrScene::PbrScene() {
    // lights
    lightPositions[0] = glm::vec3(0.0f, 0.0f, 10.0f);
    lightColors[0] = glm::vec3(150.0f, 150.0f, 150.0f);
}

void PbrScene::init() {
    camera = new TargetCamera;
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    m_pShader = new Shader("shaders/pbr/1.2.pbr.vert", "shaders/pbr/1.2.pbr.frag");

    m_pShader->use();
    m_pShader->setInt("albedoMap", 0);
    m_pShader->setInt("normalMap", 1);
    m_pShader->setInt("metallicMap", 2);
    m_pShader->setInt("roughnessMap", 3);
    m_pShader->setInt("aoMap", 4);

    // load PBR material textures
    // --------------------------
    albedo    = loadTexture("textures/pbr/rusted_iron/albedo.png");
    normal    = loadTexture("textures/pbr/rusted_iron/normal.png");
    metallic  = loadTexture("textures/pbr/rusted_iron/metallic.png");
    roughness = loadTexture("textures/pbr/rusted_iron/roughness.png");
    ao        = loadTexture("textures/pbr/rusted_iron/ao.png");
}

void PbrScene::resize(int width, int height) {
    camera->setAspec((float) width / (float) height);
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

void PbrScene::draw() {
    camera->update();
    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(m_pShader)
    {
        m_pShader->use();
        glm::mat4 projection = camera->getProjectionMatrix();
        glm::mat4 view = camera->getViewMatrix();
        m_pShader->setMat4("projection", projection);
        m_pShader->setMat4("view", view);
        m_pShader->setVec3("camPos", camera->getPosition());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, albedo);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, normal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, metallic);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, roughness);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, ao);

        // render rows*column number of spheres with material properties defined by textures (they all have the same material properties)
        glm::mat4 model = glm::mat4(1.0f);
        for (int row = 0; row < nrRows; ++row)
        {
            for (int col = 0; col < nrColumns; ++col)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(
                        (float)(col - (nrColumns / 2)) * spacing,
                        (float)(row - (nrRows / 2)) * spacing,
                        0.0f
                ));
                m_pShader->setMat4("model", model);
                m_pShader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
                renderSphere();
            }
        }

        // render light source (simply re-render sphere at light positions)
        // this looks a bit off as we use the same shader, but it'll make their positions obvious and
        // keeps the codeprint small.
        for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
        {
            glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(GetEscapeSecs() * 5.0) * 5.0, 0.0, 0.0);
            newPos = lightPositions[i];
            m_pShader->setVec3("lightPositions[" + std::to_string(i) + "]", newPos);
            m_pShader->setVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);

            model = glm::mat4(1.0f);
            model = glm::translate(model, newPos);
            model = glm::scale(model, glm::vec3(0.5f));
            m_pShader->setMat4("model", model);
            m_pShader->setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
            renderSphere();
        }
    }
}

void PbrScene::destroy() {
    if (m_pShader)
    {
        delete m_pShader;
        m_pShader = nullptr;
    }
    if (sphereVAO != 0)
    {
        glDeleteVertexArrays(1, &sphereVAO);
        sphereVAO = 0;
    }
    delete camera;
}

PbrScene::~PbrScene() {

}

std::map<std::string, std::any> PbrScene::propertyEvent(std::map<std::string, std::any> &map) {
    auto eventIdIt = map.find("event_id");
    if (eventIdIt != map.end() && eventIdIt->second.type() == typeid(std::string)) {
        auto eventIdStr = std::any_cast<std::string>(eventIdIt->second);
        if ("target_camera_touching_event" == eventIdStr) {
            parseTargetCameraEvent(map);
        }
    }
    return {};
}

void PbrScene::parseTargetCameraEvent(std::map<std::string, std::any> &event) {
    auto* targetCamera = dynamic_cast<TargetCamera*>(camera);
    if (!targetCamera) return;

    if (auto it = event.find("single_touching"); it != event.end()) {
        if (it->second.type() == typeid(std::vector<float>)) {
            const auto& val = std::any_cast<const std::vector<float>&>(it->second);
            if (val.size() >= 4) {
                targetCamera->onSingleTouching(glm::vec2(val[0], val[1]), glm::vec2(val[2], val[3]));
            }
        }
    }

    if (auto it = event.find("double_touching"); it != event.end()) {
        if (it->second.type() == typeid(std::vector<float>)) {
            const auto& val = std::any_cast<const std::vector<float>&>(it->second);
            if (val.size() >= 8) {
                targetCamera->onDoubleTouching(glm::vec2(val[0], val[1]), glm::vec2(val[2], val[3]),
                                               glm::vec2(val[4], val[5]), glm::vec2(val[6], val[7]));
            }
        }
    }

    if (event.find("reset") != event.end()) {
        targetCamera->reset();
    }
}

void PbrScene::renderSphere() {
    if (sphereVAO == 0)
    {
        glGenVertexArrays(1, &sphereVAO);

        unsigned int vbo, ebo;
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> uv;
        std::vector<glm::vec3> normals;
        std::vector<unsigned int> indices;

        const unsigned int X_SEGMENTS = 64;
        const unsigned int Y_SEGMENTS = 64;
        const float PI = 3.14159265359f;
        for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
        {
            for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
            {
                float xSegment = (float)x / (float)X_SEGMENTS;
                float ySegment = (float)y / (float)Y_SEGMENTS;
                float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
                float yPos = std::cos(ySegment * PI);
                float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

                positions.push_back(glm::vec3(xPos, yPos, zPos));
                uv.push_back(glm::vec2(xSegment, ySegment));
                normals.push_back(glm::vec3(xPos, yPos, zPos));
            }
        }

        bool oddRow = false;
        for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
        {
            if (!oddRow) // even rows: y == 0, y == 2; and so on
            {
                for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
                {
                    indices.push_back(y * (X_SEGMENTS + 1) + x);
                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                }
            }
            else
            {
                for (int x = X_SEGMENTS; x >= 0; --x)
                {
                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                    indices.push_back(y * (X_SEGMENTS + 1) + x);
                }
            }
            oddRow = !oddRow;
        }
        indexCount = static_cast<unsigned int>(indices.size());

        std::vector<float> data;
        for (unsigned int i = 0; i < positions.size(); ++i)
        {
            data.push_back(positions[i].x);
            data.push_back(positions[i].y);
            data.push_back(positions[i].z);
            if (normals.size() > 0)
            {
                data.push_back(normals[i].x);
                data.push_back(normals[i].y);
                data.push_back(normals[i].z);
            }
            if (uv.size() > 0)
            {
                data.push_back(uv[i].x);
                data.push_back(uv[i].y);
            }
        }
        glBindVertexArray(sphereVAO);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        unsigned int stride = (3 + 2 + 3) * sizeof(float);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
    }

    glBindVertexArray(sphereVAO);
    glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
}
