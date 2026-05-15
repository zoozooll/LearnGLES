#ifndef LEARNGLES_BLENDINGSCENE_H
#define LEARNGLES_BLENDINGSCENE_H

#include "Scene.h"

#include <vector>

class Camera;

class Shader;

class BlendingScene : public Scene {
public :
    BlendingScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~BlendingScene();

private:
    Camera* m_camera = nullptr;
    Shader* m_pShader = nullptr;
    unsigned int m_cubeVAO = 0u;
    unsigned int m_cubeVBO = 0u;
    unsigned int m_planeVAO = 0u;
    unsigned int m_planeVBO = 0u;
    unsigned int m_transparentVAO = 0u;
    unsigned int m_transparentVBO = 0u;

    unsigned int m_cubeTexture = 0u;
    unsigned int m_floorTexture = 0u;
    unsigned int m_transparentTexture = 0u;

    std::vector<glm::vec3> m_windows;
};

#endif //LEARNGLES_BLENDINGSCENE_H
