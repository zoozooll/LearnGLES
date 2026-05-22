#ifndef LEARNGLES_PBRSCENE_H
#define LEARNGLES_PBRSCENE_H

#include "Scene.h"

class Camera;
class Shader;

class PbrScene : public Scene {
public :
    PbrScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~PbrScene();

private:
    Camera* camera = nullptr;
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
};

#endif //LEARNGLES_PBRSCENE_H
