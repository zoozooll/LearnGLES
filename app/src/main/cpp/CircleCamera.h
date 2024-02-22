//
// Created by Aaron Lee on 2023/10/30.
//

#ifndef LEARNGLES_CIRCLECAMERA_H
#define LEARNGLES_CIRCLECAMERA_H

#include <glm/glm.hpp>

//using namespace glm;

class CircleCamera {
public:
    CircleCamera();

    void setVdy(float vdy);

    void setAspec(float aspec);

    void setNear(float near);

    void setFar(float far);

    void moveRound(const glm::vec2& round);

    void moveZoom(const float& radius);

    void moveTranslate(const glm::vec2& tran);

    void setRadius(float radius);

    glm::mat4 getProjectionMatrix();

    glm::mat4 GetViewMatrix();

    void updateCamera();

    void testSingleClick();

private:
    glm::mat4 calculatorViewMatrix(const glm::vec3 &position, const glm::vec3 &right, const glm::vec3 &up, const glm::vec3 &forward) ;

    float m_vdy = 75.f;
    float m_aspec = 0.f;
    float m_near = 0.f;
    float m_far = 0.f;


    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;

    glm::vec3 m_target = {0.f, 0.f, 0.f};
    float m_radius = 8.f;
    float m_longitude = glm::radians(-90.f);  // 经度
    float m_latitude = 0.f; // 纬度
    glm::vec3 m_up = {0.f, 1.f, 0.f};
};


#endif //LEARNGLES_CIRCLECAMERA_H
