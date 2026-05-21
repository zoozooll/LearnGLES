#ifndef LEARNGLES_PARALLAXMAPPINGSCENE_H
#define LEARNGLES_PARALLAXMAPPINGSCENE_H

#include "Scene.h"

class Camera;
class Shader;

class ParallaxMappingScene : public Scene {
public :
    ParallaxMappingScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~ParallaxMappingScene();

private:
    void renderQuad();

    Camera* camera = nullptr;
    Shader* m_pShader = nullptr;
    unsigned int m_quadVAO = 0u;
    unsigned int m_quadVBO = 0u;

    unsigned int m_diffuseMap = 0u;
    unsigned int m_normalMap = 0u;
    unsigned int m_heightMap = 0u;

    glm::vec3 m_lightPos = glm::vec3(0.5f, 1.0f, 0.3f);

    // Properties
    float heightScale = 0.f;
};

#endif //LEARNGLES_PARALLAXMAPPINGSCENE_H
