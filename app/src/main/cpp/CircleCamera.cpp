//
// Created by huion on 2023/10/30.
//

#include "CircleCamera.h"
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "logutil.h"

void CircleCamera::moveRound(const vec2 &round) {

    updateCamera();
}

void CircleCamera::moveZoom(const float &radius) {

}

void CircleCamera::moveTranslate(const vec2 &tran) {

}


void CircleCamera::updateCamera() {
    float x = m_radius * cosf(radians(m_latitude)) * cosf(radians(m_longitude));
    float y = m_radius * sinf(radians(m_latitude));
    float z = m_radius * cosf(radians(m_latitude)) * sinf(radians(m_longitude));

    vec3 position(x, y, z);
    vec3 forward(normalize(m_target - position));
    vec3 right(normalize(cross(forward, m_up)));
    vec3 up(normalize(cross(right, forward)));
    m_up = up;
    m_viewMatrix = calculatorViewMatrix(position, right, up, forward);
    m_projectionMatrix = perspective(radians(m_vdy), m_aspec, m_near, m_far);
}

void CircleCamera::setVdy(float vdy) {
    CircleCamera::m_vdy = vdy;
}

void CircleCamera::setAspec(float aspec) {
    CircleCamera::m_aspec = aspec;
}

void CircleCamera::setNear(float near) {
    CircleCamera::m_near = near;
}

void CircleCamera::setFar(float far) {
    CircleCamera::m_far = far;
}

void CircleCamera::setRadius(float radius) {
    m_radius = radius;
}

mat4 CircleCamera::getProjectionMatrix() {
    return m_projectionMatrix;
}

mat4 CircleCamera::GetViewMatrix() {
    return m_viewMatrix;
}

CircleCamera::CircleCamera() {
//    m_cameraTranMatrix = translate(m_cameraTranMatrix, vec3(0.f, 0.f, m_radius));
}

void CircleCamera::testSingleClick() {
//    vec3 l_position = {m_cameraTranMatrix[3][0] / m_cameraTranMatrix[3][3],
//                       m_cameraTranMatrix[3][1] / m_cameraTranMatrix[3][3],
//                       m_cameraTranMatrix[3][2] / m_cameraTranMatrix[3][3]};
//    auto l_forward = glm::normalize(glm::vec3(m_cameraTranMatrix[0][2], m_cameraTranMatrix[1][2],
//                                              m_cameraTranMatrix[2][2]));
//    auto l_target = l_position - l_forward * m_radius;
//
//
//
//    mat4 rotateMatrix(1.f);
//    auto l_deltaTarget = vec3(0.f, 0.f, -m_radius);
////    rotateMatrix = translate(rotateMatrix, l_deltaTarget);
//    rotateMatrix = rotate(rotateMatrix, radians(-90.f), vec3(0.f, 1.f, 0.f));
////    rotateMatrix = rotate(rotateMatrix, round.y, vec3(1.f, 0.f, 0.f));
////    rotateMatrix = translate(rotateMatrix, -l_deltaTarget);
//    m_cameraTranMatrix = rotateMatrix * m_cameraTranMatrix;
//    updateCamera();
}

mat4 CircleCamera::calculatorViewMatrix(const vec3 &position, const vec3 &right, const vec3 &up, const vec3 &forward) {
    mat4 Result(1);
    Result[0][0] = right.x;
    Result[1][0] = right.y;
    Result[2][0] = right.z;
    Result[0][1] = up.x;
    Result[1][1] = up.y;
    Result[2][1] = up.z;
    Result[0][2] =-forward.x;
    Result[1][2] =-forward.y;
    Result[2][2] =-forward.z;
    Result[3][0] =-dot(right, position);
    Result[3][1] =-dot(up, position);
    Result[3][2] = dot(forward, position);
    return Result;
}
