#ifndef LEARNGLES_NORMALMAPPINGSCENE_H
#define LEARNGLES_NORMALMAPPINGSCENE_H

#include "Scene.h"

class Camera;
class Shader;

class NormalMappingScene : public Scene {
public :
    NormalMappingScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~NormalMappingScene();

private:
    void renderQuad();

    Camera* camera;
    Shader* m_pShader;
    unsigned int m_quadVAO;
    unsigned int m_quadVBO;

    unsigned int m_diffuseMap;
    unsigned int m_normalMap;

    glm::vec3 m_lightPos;
};

#endif //LEARNGLES_NORMALMAPPINGSCENE_H
