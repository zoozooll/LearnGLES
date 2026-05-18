#ifndef LEARNGLES_INSTANCESCENE_H
#define LEARNGLES_INSTANCESCENE_H

#include "Scene.h"

class Shader;
class Camera;

class InstanceScene : public Scene {
public :
    InstanceScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~InstanceScene();

private:
    Camera* m_camera = nullptr;
    Shader* m_pShader = nullptr;
    unsigned int m_quadVAO = 0u;
    unsigned int m_quadVBO = 0u;
    unsigned int m_instanceVBO = 0u;
};

#endif //LEARNGLES_INSTANCESCENE_H
