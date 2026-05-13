//
// Created by Aaron Lee on 2023/08/03.
//

#include "Camera.h"

#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

#include "logutil.h"

using glm::vec2;
using glm::vec3;
using glm::mat3;
using glm::mat4;
using glm::radians;
using glm::perspective;

void Camera::start() {
    viewDirty = true;
    projectionDirty = true;
}

void Camera::setVdy(float mVdy) {
    m_vdy = mVdy;
    projectionDirty = true;
}

void Camera::setAspec(float mAspec) {
    m_aspec = mAspec;
    projectionDirty = true;
}

void Camera::setNear(float mNear) {
    m_near = mNear;
    projectionDirty = true;
}

void Camera::setFar(float mFar) {
    m_far = mFar;
    projectionDirty = true;
}

const mat4 &Camera::getViewMatrix() const {
    return m_viewMatrix;
}

const mat4 &Camera::getProjectionMatrix() const {
    return m_projectionMatrix;
}

const vec3 &Camera::getPosition() const {
    return m_position;
}

mat4 Camera::getVPMatrix() const {
    return m_projectionMatrix * m_viewMatrix;
}

void Camera::update() {
    if (viewDirty) {
        m_viewMatrix = lookAt(m_position, m_targetPosition, m_up);
        viewDirty = false;
    }
    if (projectionDirty) {
        m_projectionMatrix = glm::perspective(glm::radians(m_vdy), m_aspec, m_near, m_far);
        projectionDirty = false;
    }
}

float Camera::getNear() const {
    return m_near;
}

float Camera::getFar() const {
    return m_far;
}

float Camera::getVdy() const {
    return m_vdy;
}

void Camera::reset() {
    m_vdy = CAMERA_FOVY_DEGREE;
    m_aspec = 0.f;
    m_near = CAMERA_NEAR;
    m_far = CAMERA_FAR;
}

const vec3 &Camera::getTargetPosition() const {
    return m_targetPosition;
}

void Camera::setTargetPosition(const vec3 &targetPosition) {
    m_targetPosition = targetPosition;
    viewDirty = true;
}

const vec3 &Camera::getUp() const {
    return m_up;
}

void Camera::setUp(const vec3 &up) {
    m_up = up;
    viewDirty = true;
}

void Camera::setPosition(const vec3 &position) {
    m_position = position;
    viewDirty = true;
}
