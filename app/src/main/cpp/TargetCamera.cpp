//
// Created by Aaron Lee on 2023/10/31.
//

#include "TargetCamera.h"

#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

#include "logutil.h"

using glm::vec2;
using glm::vec3;
using glm::mat4;
using glm::radians;
using glm::perspective;

void TargetCamera::updateCameraMatrix() {
    vec3 target(m_targetTransform[3][0] / m_targetTransform[3][3], m_targetTransform[3][1] / m_targetTransform[3][3],
                m_targetTransform[3][2] / m_targetTransform[3][3]);
    vec3 right   (m_targetTransform[0][0], m_targetTransform[1][0], m_targetTransform[2][0]);
    vec3 up      (m_targetTransform[0][1], m_targetTransform[1][1], m_targetTransform[2][1]);
    vec3 forward (m_targetTransform[0][2], m_targetTransform[1][2], m_targetTransform[2][2]);
    right = normalize(right);
    up = normalize(up);
    forward = normalize(forward);

    cameraPosition = target + forward * m_radius;
    LOGI(__FILE_NAME__, "updateCameraMatrix cameraPosition: %s, target: %s, up: %s",
         to_string(cameraPosition).c_str(),  to_string(target).c_str(), to_string(up).c_str());
    m_viewMatrix = lookAt(cameraPosition, target, up);
    m_projectionMatrix = perspective(radians(m_vdy), m_aspec, m_near, m_far);

}

void TargetCamera::move(const vec2 &move) {
    vec3 target(m_targetTransform[3][0] / m_targetTransform[3][3], m_targetTransform[3][1] / m_targetTransform[3][3],
                m_targetTransform[3][2] / m_targetTransform[3][3]);
    vec3 right   (m_targetTransform[0][0], m_targetTransform[1][0], m_targetTransform[2][0]);
    vec3 up      (m_targetTransform[0][1], m_targetTransform[1][1], m_targetTransform[2][1]);
    right = normalize(right);
    up = normalize(up);
    vec3 targetTranslate = move.x * right + move.y * up;
    mat4 l_matrix = translate(mat4(1.f), targetTranslate);
    m_targetTransform = l_matrix * m_targetTransform;
    updateCameraMatrix();
}

void TargetCamera::zoom(const float &zoom) {
    m_radius *= zoom;
    updateCameraMatrix();
}

void TargetCamera::yawPitch(const vec2 &director) {
    glm::mat4 l_matrix(1.0f);
    glm::vec2 perpendicular = glm::normalize(glm::vec2(-director.y, director.x));
    auto angle = glm::length(director) * 0.1f / M_PI;
    l_matrix = glm::rotate(l_matrix, float(angle), glm::vec3(perpendicular, 0.f) );
    m_targetTransform = l_matrix * m_targetTransform;
    updateCameraMatrix();
}

void TargetCamera::roll(const float &angle) {

}

void TargetCamera::setRadius(float mRadius) {
    m_radius = mRadius;
}

void TargetCamera::setVdy(float mVdy) {
    m_vdy = mVdy;
}

void TargetCamera::setAspec(float mAspec) {
    m_aspec = mAspec;
}

void TargetCamera::setNear(float mNear) {
    m_near = mNear;
}

void TargetCamera::setFar(float mFar) {
    m_far = mFar;
}

const mat4 &TargetCamera::getViewMatrix() const {
    return m_viewMatrix;
}

const mat4 &TargetCamera::getProjectionMatrix() const {
    return m_projectionMatrix;
}

const vec3 &TargetCamera::getCameraPosition() const {
    return cameraPosition;
}
