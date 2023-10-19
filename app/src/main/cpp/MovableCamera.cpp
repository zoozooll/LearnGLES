//
// Created by huion on 2023/4/10.
//

#include "MovableCamera.h"

#include <glm/ext.hpp>

void MovableCamera::calculateViewTransform() {
    float x = m_radius * cosf(radians(m_latitude)) * cosf(radians(m_longitude));
    float y = m_radius * sinf(radians(m_latitude));
    float z = m_radius * cosf(radians(m_latitude)) * sinf(radians(m_longitude));
    glm::vec3 position = {x, y, z};
    glm::vec3 target(0.f);
    glm::vec3 up(0.f, 1.f, 0.f);
    viewMatrix = lookAt(position, target, up);
}

void MovableCamera::zoom(float radius) {
    m_radius *= 1.0f / radius;
}

void MovableCamera::rotateHorizontal(float degrees) {
    m_longitude += degrees;
}

void MovableCamera::rotateVirtual(float degrees) {
    m_latitude += degrees;
    m_latitude = fclamp(m_latitude, -85.f, 85.f);
}

void MovableCamera::setRadius(float radius) {
    m_radius = radius;
}

void MovableCamera::setLongitude(float longitude) {
    m_longitude = longitude;
}

void MovableCamera::setLatitude(float latitude) {
    m_latitude = latitude;
}

const mat4 &MovableCamera::GetViewMatrix() {
    calculateViewTransform();
    return viewMatrix;
}

const vec3 &MovableCamera::getPosition() const {
    return position;
}

