#include "AreaLightsScene.h"

#include <random>

#include "colors.hpp"
#include "Shader.h"
#include "Texture.h"
#include "TargetCamera.h"
#include "ltc_matrix.hpp"

const glm::vec3 LIGHT_COLOR = Color::BurlyWood;

const float psize = 10.0f;

VertexAL planeVertices[6] = {
        { {-psize, 0.0f, -psize}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f} },
        { {-psize, 0.0f,  psize}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f} },
        { { psize, 0.0f,  psize}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f} },
        { {-psize, 0.0f, -psize}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f} },
        { { psize, 0.0f,  psize}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f} },
        { { psize, 0.0f, -psize}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f} }
};
VertexAL areaLightVertices[6] = {
        { {-8.0f, 2.4f, -1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
        { {-8.0f, 2.4f,  1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f} },
        { {-8.0f, 0.4f,  1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} },
        { {-8.0f, 2.4f, -1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
        { {-8.0f, 0.4f,  1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} },
        { {-8.0f, 0.4f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f} }
};

AreaLightsScene::AreaLightsScene() {
}

void AreaLightsScene::init() {
    glEnable(GL_DEPTH_TEST);
    mat1 = loadMTexture();
    mat2 = loadLUTTexture();
    shaderLTC = new Shader("shaders/area_lights/7.multi_area_light.vert", "shaders/area_lights/7.multi_area_light.frag");
    shaderLightPlane = new Shader("shaders/area_lights/7.light_plane.vert", "shaders/area_lights/7.light_plane.frag");
    concreteTexture = loadTexture("textures/concreteTexture.png", true);

    configurePlane();
    configureAreaLights();

    shaderLTC->use();
    for (int i = 0; i < NUM_AREA_LIGHTS; i++)
    {
        glm::mat4 model(1.0f);
        model = glm::translate(model, areaLights[i].offset);
        model = glm::rotate(model, areaLights[i].yRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 p0 = glm::vec3(model * glm::vec4(areaLightVertices[0].position, 1.0f));
        glm::vec3 p1 = glm::vec3(model * glm::vec4(areaLightVertices[1].position, 1.0f));
        glm::vec3 p2 = glm::vec3(model * glm::vec4(areaLightVertices[4].position, 1.0f));
        glm::vec3 p3 = glm::vec3(model * glm::vec4(areaLightVertices[5].position, 1.0f));
        std::string base = "areaLights[" + std::to_string(i) + "].";
        shaderLTC->setVec3(base + "points[0]", p0);
        shaderLTC->setVec3(base + "points[1]", p1);
        shaderLTC->setVec3(base + "points[2]", p2);
        shaderLTC->setVec3(base + "points[3]", p3);
        shaderLTC->setVec3(base + "color", areaLights[i].color);
        shaderLTC->setFloat(base + "intensity", 2.0f);
        shaderLTC->setInt(base + "twoSided", 1);
    }
    shaderLTC->setInt("numAreaLights", NUM_AREA_LIGHTS);
    shaderLTC->setInt("LTC1", 0);
    shaderLTC->setInt("LTC2", 1);
    shaderLTC->setInt("material.diffuse", 2);
    incrementRoughness(0.0f);

    shaderLightPlane->use();
    shaderLightPlane->setVec3("lightColor", LIGHT_COLOR);

    glGenQueries(1, &timeQuery);
}

void AreaLightsScene::resize(int width, int height) {
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

void AreaLightsScene::draw() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderLTC->use();
    glm::mat4 model(1.0f);
    shaderLTC->setMat4("model", model);
    shaderLTC->setMat3("normalMatrix", glm::mat3(model));
    glm::mat4 view = camera->getViewMatrix();
    shaderLTC->setMat4("view", view);
    glm::mat4 projection = camera->getProjectionMatrix();
    shaderLTC->setMat4("projection", projection);
    shaderLTC->setVec3("viewPosition", camera->getPosition());

    glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, mat1);
    glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, mat2);
    glActiveTexture(GL_TEXTURE2); glBindTexture(GL_TEXTURE_2D, concreteTexture);

    glBeginQuery(GL_TIME_ELAPSED, timeQuery);
    renderPlane();
    glEndQuery(GL_TIME_ELAPSED);

    shaderLightPlane->use();
    shaderLightPlane->setMat4("view", view);
    shaderLightPlane->setMat4("projection", projection);
    for (int i = 0; i < NUM_AREA_LIGHTS; i++)
    {
        model = glm::translate(glm::mat4(1.0f), areaLights[i].offset);
        model = glm::rotate(model, areaLights[i].yRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        shaderLightPlane->setMat4("model", model);
        shaderLightPlane->setVec3("lightColor", areaLights[i].color);
        renderAreaLight();
    }

    GLuint64 elapsed = 0;
    glGetQueryObjectui64v(timeQuery, GL_QUERY_RESULT, &elapsed);
    numQueries++;
    totalQueryTimeNs += elapsed;
}

void AreaLightsScene::destroy() {
    double measuredAverageMs = ((double)totalQueryTimeNs / (double)numQueries) * 1.0e-6;

    if (shaderLTC)
        delete shaderLTC;
    if (shaderLightPlane)
        delete shaderLightPlane;
    glDeleteQueries(1, &timeQuery);
    glDeleteVertexArrays(1, &planeVAO);
    glDeleteBuffers(1, &planeVBO);
    glDeleteVertexArrays(1, &areaLightVAO);
    glDeleteBuffers(1, &areaLightVBO);
    glDeleteTextures(1, &mat1);
    glDeleteTextures(1, &mat2);
    glDeleteTextures(1, &concreteTexture);
    delete camera;
}

AreaLightsScene::~AreaLightsScene() {

}

void AreaLightsScene::configurePlane() {
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
}

void AreaLightsScene::configureAreaLights() {
    std::uniform_real_distribution<GLfloat> random_floats(0.0f, 1.0f);
    std::default_random_engine generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    auto fn = [&](){
        return random_floats(generator);
    };
    for (int i = 0; i < NUM_AREA_LIGHTS; i++) {
        float x = fn();
        x = (x > 0.5f) ? x : -x;
        float z = fn();
        z = (z > 0.5f) ? z : -z;
        areaLights[i].offset = glm::vec3(x, 0.0f, z) * 8.f;
        areaLights[i].yRotation = fn() * glm::two_pi<float>();
        areaLights[i].color = glm::vec3(fn(), fn(), fn());
    }
    glGenVertexArrays(1, &areaLightVAO);
    glGenBuffers(1, &areaLightVBO);
    glBindVertexArray(areaLightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, areaLightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(areaLightVertices), areaLightVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
}

void AreaLightsScene::renderPlane() {
    glBindVertexArray(planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void AreaLightsScene::renderAreaLight() {
    glBindVertexArray(areaLightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

unsigned int AreaLightsScene::loadMTexture() {
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_FLOAT, LTC1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

unsigned int AreaLightsScene::loadLUTTexture() {
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_FLOAT, LTC2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

void AreaLightsScene::incrementRoughness(float step) {
    static float roughness = 0.5f;
    roughness += step;
    roughness = glm::clamp(roughness, 0.0f, 1.0f);
    if (shaderLTC) {
        shaderLTC->use();
        shaderLTC->setVec4("material.albedoRoughness", glm::vec4(Color::SlateGray, roughness));
    }
}
