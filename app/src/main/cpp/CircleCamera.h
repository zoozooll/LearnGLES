//
// Created by huion on 2023/10/30.
//

#ifndef LEARNGLES_CIRCLECAMERA_H
#define LEARNGLES_CIRCLECAMERA_H

#include <glm/glm.hpp>

using namespace glm;

class CircleCamera {
public:
    CircleCamera();

    void setVdy(float vdy);

    void setAspec(float aspec);

    void setNear(float near);

    void setFar(float far);

    void moveRound(const vec2& round);

    void moveZoom(const float& radius);

    void moveTranslate(const vec2& tran);

    void setRadius(float radius);

    glm::mat4 getProjectionMatrix();

    glm::mat4 GetViewMatrix();

    void updateCamera();

    void testSingleClick();

private:
    mat4 calculatorViewMatrix(const vec3 &position, const vec3 &right, const vec3 &up, const vec3 &forward) ;

    float m_vdy = 75.f;
    float m_aspec = 0.f;
    float m_near = 0.f;
    float m_far = 0.f;


    mat4 m_viewMatrix;
    mat4 m_projectionMatrix;

    vec3 m_target = {0.f, 0.f, 0.f};
    float m_radius = 8.f;
    float m_longitude = radians(-90.f);  // 经度
    float m_latitude = 0.f; // 纬度
    vec3 m_up = {0.f, 1.f, 0.f};
};


#endif //LEARNGLES_CIRCLECAMERA_H
