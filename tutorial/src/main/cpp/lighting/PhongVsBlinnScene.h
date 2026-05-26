#ifndef LEARNGLES_PHONGVSBLINNSCENE_H
#define LEARNGLES_PHONGVSBLINNSCENE_H

#include "TutorialScene.h"

#include <glm/glm.hpp>

class Camera;
class Shader;

class PhongVsBlinnScene : public TutorialScene {
public :
    PhongVsBlinnScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~PhongVsBlinnScene();

private:
    Camera* m_camera = nullptr;
    Shader* m_pShader = nullptr;
    unsigned int m_planeVAO = 0u;
    unsigned int m_planeVBO = 0u;
    unsigned int m_floorTexture = 0u;
    glm::vec3 m_lightPos;

    bool blinn = true;
public:
    bool isBlinn() const;

    void setBlinn(bool blinn);
};

#endif //LEARNGLES_PHONGVSBLINNSCENE_H
