#ifndef LEARNGLES_FRUSTUMCULLINGSCENE_H
#define LEARNGLES_FRUSTUMCULLINGSCENE_H

#include <memory>
#include "TutorialScene.h"

class Shader;
class Camera;
class Entity;
class Model;

class FrustumCullingScene : public TutorialScene {
public :
    FrustumCullingScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~FrustumCullingScene();

private:
    Camera* m_camera = nullptr;
    Camera* m_cameraSpy = nullptr;
    Shader* ourShader = nullptr;
    Entity* ourEntity = nullptr;
    std::unique_ptr<Model> m_model;

    int m_width = 0;
    int m_height = 0;

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_FRUSTUMCULLINGSCENE_H
