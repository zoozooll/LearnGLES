#ifndef LEARNGLES_ASTEROIDSCENE_H
#define LEARNGLES_ASTEROIDSCENE_H

#include "TutorialScene.h"

class Shader;
class Camera;
class Model;

class AsteroidScene : public TutorialScene {
public :
    AsteroidScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~AsteroidScene();

private:
    Camera *m_camera = nullptr;
    Shader* m_pAsteroidShader = nullptr;
    Shader* m_pPlanetShader = nullptr;
    Model* m_pRockModel = nullptr;
    Model* m_pPlanetModel = nullptr;
    unsigned int m_instanceBuffer = 0u;
    unsigned int m_amount = 0u;

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_ASTEROIDSCENE_H
