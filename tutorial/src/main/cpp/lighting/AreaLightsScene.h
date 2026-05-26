#ifndef LEARNGLES_AREALIGHTSSCENE_H
#define LEARNGLES_AREALIGHTSSCENE_H

#include "TutorialScene.h"

class Shader;
class Camera;

struct VertexAL {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;
};

struct AreaLight {
    glm::vec3 offset;
    float yRotation;
    glm::vec3 color;
    float intensity = 4.0f;
    bool twoSided = true;
};

class AreaLightsScene : public TutorialScene {
public :
    AreaLightsScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~AreaLightsScene();

private:
    Camera* camera = nullptr;
    Shader* shaderLTC = nullptr;
    Shader* shaderLightPlane = nullptr;

    unsigned int planeVBO = 0u, planeVAO = 0u;
    unsigned int areaLightVBO = 0u, areaLightVAO = 0u;
    unsigned int mat1 = 0u, mat2 = 0u;
    unsigned int concreteTexture = 0u;

    static const int NUM_AREA_LIGHTS = 16;
    AreaLight areaLights[NUM_AREA_LIGHTS];

    unsigned int timeQuery = 0u;
    unsigned long long totalQueryTimeNs = 0ul;
    unsigned long long numQueries = 0ul;

    int m_width = 0;
    int m_height = 0;
    bool keys[1024] = {false};

    void configurePlane();
    void configureAreaLights();
    void renderPlane();
    void renderAreaLight();
    unsigned int loadMTexture();
    unsigned int loadLUTTexture();
    void incrementRoughness(float step);
};

#endif //LEARNGLES_AREALIGHTSSCENE_H
