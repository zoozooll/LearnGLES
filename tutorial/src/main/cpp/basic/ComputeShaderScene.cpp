#include "ComputeShaderScene.h"

#include "Shader.h"
#include "ComputeShader.h"
#include "Texture.h"
#include "TimeUtil.h"
#include "Camera.h"
#include "TargetCamera.h"

const unsigned int TEXTURE_WIDTH = 512, TEXTURE_HEIGHT = 512;

ComputeShaderScene::ComputeShaderScene() {

}

void ComputeShaderScene::init() {
    m_camera = new TargetCamera;
    m_screenQuadShader = new Shader("shaders/compute_shader/screenQuad.vert", "shaders/compute_shader/screenQuad.frag");
    m_computeShader = new ComputeShader("shaders/compute_shader/computeShader.comp");

    m_screenQuadShader->use();
    m_screenQuadShader->setInt("tex", 0);

    m_texture = genTexture(TEXTURE_WIDTH, TEXTURE_HEIGHT, 4);
    glBindImageTexture(0, m_texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
}

void ComputeShaderScene::resize(int width, int height) {
    m_camera->setAspec((float) width / (float) height);
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

void ComputeShaderScene::draw() {
    m_camera->update();
    m_computeShader->use();
    m_computeShader->setFloat("t", GetEscapeSecs());
    glDispatchCompute((unsigned int)TEXTURE_WIDTH/10, (unsigned int)TEXTURE_HEIGHT/10, 1);

    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_screenQuadShader->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    renderQuad();
}

void ComputeShaderScene::destroy() {
    if (m_screenQuadShader) delete m_screenQuadShader;
    if (m_computeShader) delete m_computeShader;
    glDeleteTextures(1, &m_texture);
    glDeleteVertexArrays(1, &m_quadVAO);
    glDeleteBuffers(1, &m_quadVBO);
    delete m_camera;
}

ComputeShaderScene::~ComputeShaderScene() {

}

std::map<std::string, std::any> ComputeShaderScene::propertyEvent(std::map<std::string, std::any> &map) {
    auto eventIdIt = map.find("event_id");
    if (eventIdIt != map.end() && eventIdIt->second.type() == typeid(std::string)) {
        auto eventIdStr = std::any_cast<std::string>(eventIdIt->second);
        if ("target_camera_touching_event" == eventIdStr) {
            parseTargetCameraEvent(map);
        }
    }
    return {};
}

void ComputeShaderScene::parseTargetCameraEvent(std::map<std::string, std::any> &event) {
    auto* targetCamera = dynamic_cast<TargetCamera*>(m_camera);
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

void ComputeShaderScene::renderQuad()
{
    if (m_quadVAO == 0)
    {
        float quadVertices[] = {
                // positions        // texture Coords
                -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        glGenVertexArrays(1, &m_quadVAO);
        glGenBuffers(1, &m_quadVBO);
        glBindVertexArray(m_quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(m_quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}
