#ifndef LEARNGLES_MULTILIGHTSSCENE_H
#define LEARNGLES_MULTILIGHTSSCENE_H

#include "Scene.h"

#include <vector>

class Shader;
class Camera;

class MultiLightsScene : public Scene {
public :
    MultiLightsScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~MultiLightsScene();

private:
    Camera* m_camera = nullptr;

    Shader* m_pLightingShader = nullptr;
    Shader* m_pLightCubeShader = nullptr;
    unsigned int m_cubeVAO = 0u;
    unsigned int m_lightCubeVAO = 0u;
    unsigned int m_VBO = 0u;
    unsigned int m_diffuseMap = 0u;
    unsigned int m_specularMap = 0u;
    glm::vec3 m_cubePositions[10];
    glm::vec3 m_pointLightPositions[4];
};

#endif //LEARNGLES_MULTILIGHTSSCENE_H
