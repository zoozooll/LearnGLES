#ifndef LEARNGLES_FRUSTUMCULLINGSCENE_H
#define LEARNGLES_FRUSTUMCULLINGSCENE_H

#include "TutorialScene.h"

class Shader;
class Camera;
class Entity;

class FrustumCullingScene : public TutorialScene {
public :
    FrustumCullingScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~FrustumCullingScene();

private:
    Camera* m_camera = nullptr;
    Camera* m_cameraSpy = nullptr;
    Shader* ourShader = nullptr;;
    Entity* ourEntity = nullptr;;

    int m_width = 0;
    int m_height = 0;
};

#endif //LEARNGLES_FRUSTUMCULLINGSCENE_H
