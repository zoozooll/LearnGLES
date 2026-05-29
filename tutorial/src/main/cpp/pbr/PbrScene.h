#ifndef LEARNGLES_PBRSCENE_H
#define LEARNGLES_PBRSCENE_H

#include "TutorialScene.h"

class Camera;
class Shader;

class PbrScene : public TutorialScene {
public :
    PbrScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~PbrScene();

private:
    Camera* m_camera = nullptr;
    Shader* m_pShader = nullptr;

    unsigned int sphereVAO = 0u;
    unsigned int indexCount = 0u;
    void renderSphere();

    unsigned int albedo = 0u, normal = 0u, metallic = 0u, roughness = 0u, ao = 0u;

    glm::vec3 lightPositions[1];
    glm::vec3 lightColors[1];
    int nrRows = 0;
    int nrColumns = 0;
    float spacing = 0.f;

    int m_width = 0;
    int m_height = 0;

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_PBRSCENE_H
