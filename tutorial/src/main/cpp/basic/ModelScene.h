#ifndef LEARNGLES_MODELSCENE_H
#define LEARNGLES_MODELSCENE_H

#include "TutorialScene.h"

class Shader;
class Model;
class Camera;

class ModelScene : public TutorialScene {
public :
    ModelScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~ModelScene();

private:
    Camera* m_camera = nullptr;
    Shader* m_pShader = nullptr;
    Model* m_pModel = nullptr;

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_MODELSCENE_H
