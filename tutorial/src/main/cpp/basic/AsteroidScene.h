#ifndef LEARNGLES_ASTEROIDSCENE_H
#define LEARNGLES_ASTEROIDSCENE_H

#include "Scene.h"

class Shader;
class Camera;
class Model;

class AsteroidScene : public Scene {
public :
    AsteroidScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~AsteroidScene();

private:
    Camera *m_camera = nullptr;
    Shader* m_pAsteroidShader = nullptr;
    Shader* m_pPlanetShader = nullptr;
    Model* m_pRockModel = nullptr;
    Model* m_pPlanetModel = nullptr;
    unsigned int m_instanceBuffer = 0u;
    unsigned int m_amount = 0u;
};

#endif //LEARNGLES_ASTEROIDSCENE_H
