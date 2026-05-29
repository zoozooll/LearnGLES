#ifndef LEARNGLES_BASICLIGHTINGSCENE_H
#define LEARNGLES_BASICLIGHTINGSCENE_H

#include "TutorialScene.h"
#include <glm/glm.hpp>

class Camera;
class Shader;

class BasicLightingScene : public TutorialScene {
public :
    BasicLightingScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~BasicLightingScene();

private:
    Camera* m_camera = nullptr;

    Shader* m_pLightingShader = nullptr;
    Shader* m_pLightCubeShader = nullptr;
    unsigned int m_cubeVAO = 0u;
    unsigned int m_lightCubeVAO = 0u;
    unsigned int m_VBO = 0u;
    unsigned int m_diffuseMap = 0u;
    unsigned int m_specularMap = 0u;
    unsigned int m_emissionMap = 0u;
    glm::vec3 m_lightPos;

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_BASICLIGHTINGSCENE_H
