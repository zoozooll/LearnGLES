#ifndef LEARNGLES_MODELSCENE_H
#define LEARNGLES_MODELSCENE_H

#include "Scene.h"

class Shader;
class Model;
class Camera;

class ModelScene : public Scene {
public :
    ModelScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~ModelScene();

private:
    Camera* m_camera = nullptr;
    Shader* m_pShader = nullptr;
    Model* m_pModel = nullptr;
};

#endif //LEARNGLES_MODELSCENE_H
