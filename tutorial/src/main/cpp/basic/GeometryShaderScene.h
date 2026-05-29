#ifndef LEARNGLES_GEOMETRYSHADERSCENE_H
#define LEARNGLES_GEOMETRYSHADERSCENE_H

#include "TutorialScene.h"

class Shader;
class Camera;

class GeometryShaderScene : public TutorialScene {
public :
    GeometryShaderScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~GeometryShaderScene();

private:
    Camera* m_camera = nullptr;
    Shader* m_pShader = nullptr;
    unsigned int m_VAO = 0u;
    unsigned int m_VBO = 0u;

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_GEOMETRYSHADERSCENE_H
