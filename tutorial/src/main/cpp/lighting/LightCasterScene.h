#ifndef LEARNGLES_LIGHTCASTERSCENE_H
#define LEARNGLES_LIGHTCASTERSCENE_H

#include "TutorialScene.h"

#include <glm/glm.hpp>

class Camera;
class Shader;

class LightCasterScene : public TutorialScene {
public :
    LightCasterScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~LightCasterScene();

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

    //region Properties
    float ambientFactor = 0.35f;
    float diffuseFactor = 0.5f;
    float specularFactor = 1.0f;
    //endregion

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_LIGHTCASTERSCENE_H
