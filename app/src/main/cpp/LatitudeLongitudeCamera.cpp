//
// Created by zoozo on 10/8/2024.
//

#include "LatitudeLongitudeCamera.h"

#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

#include "logutil.h"

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;
using glm::radians;
using glm::perspective;

void LatitudeLongitudeCamera::start() {

}

void LatitudeLongitudeCamera::move(const vec2 &screen_move) {
    auto forward = glm::normalize(m_targetPosition - m_cameraPosition);
    auto right = glm::cross(forward, CAMERA_DEF_UP);
    auto top = glm::cross(right, forward);
    m_targetPosition += right * screen_move.x * 0.01F + top * screen_move.y * 0.01F;
}

void LatitudeLongitudeCamera::zoom(const float &zoom) {
    if (zoom > 0.F) {
        radius /= zoom;
        radius = fmin(fmax(2.f, radius), 50.f);
    }
}

void LatitudeLongitudeCamera::yawPitch(const vec2 &director) {
    m_LatitudeLongitude += director;
    if (m_LatitudeLongitude.x <= -180.F) {
        m_LatitudeLongitude.x += 360.F;
    } else if (m_LatitudeLongitude.x > 180.F) {
        m_LatitudeLongitude.x -= 360.F;
    }
    m_LatitudeLongitude.y = glm::clamp(m_LatitudeLongitude.y, -85.F, 85.F);
}


void LatitudeLongitudeCamera::setRadius(float mRadius) {
    LatitudeLongitudeCamera::radius = mRadius;
}

void LatitudeLongitudeCamera::setVdy(float mVdy) {
    LatitudeLongitudeCamera::vdy = mVdy;
}

void LatitudeLongitudeCamera::setAspec(float aspec) {
    LatitudeLongitudeCamera::aspec = aspec;
}

void LatitudeLongitudeCamera::setNear(float mNear) {
    LatitudeLongitudeCamera::near = mNear;
}

void LatitudeLongitudeCamera::setFar(float mFar) {
    LatitudeLongitudeCamera::far = mFar;
}

const mat4 &LatitudeLongitudeCamera::getViewMatrix() const {
    return m_viewMatrix;
}

const mat4 &LatitudeLongitudeCamera::getProjectionMatrix() const {
    return m_projectionMatrix;
}

const vec3 &LatitudeLongitudeCamera::getPosition() const {
    return m_cameraPosition;
}

mat4 LatitudeLongitudeCamera::getVPMatrix() const {
    return m_projectionMatrix * m_viewMatrix;
}

float LatitudeLongitudeCamera::getRadius() const {
    return radius;
}

void LatitudeLongitudeCamera::update() {
    auto x = radius * glm::cos(radians(m_LatitudeLongitude.y)) * glm::sin(radians(m_LatitudeLongitude.x));
    auto y = radius * glm::sin(radians(m_LatitudeLongitude.y));
    auto z = radius * glm::cos(radians(m_LatitudeLongitude.y)) * glm::cos(radians(m_LatitudeLongitude.x));
    m_cameraPosition = m_targetPosition + vec3(x, y, z);
    m_viewMatrix = lookAt(m_cameraPosition, m_targetPosition, CAMERA_DEF_UP);
    m_projectionMatrix = glm::perspective(glm::radians(vdy), aspec, near, far);
}

float LatitudeLongitudeCamera::getNear() const {
    return near;
}

float LatitudeLongitudeCamera::getFar() const {
    return far;
}

float LatitudeLongitudeCamera::getVdy() const {
    return vdy;
}


void LatitudeLongitudeCamera::reset() {
    radius = CAMERA_DEF_RADIUS;
    vdy = CAMERA_FOVY_DEGREE;
    near = CAMERA_NEAR;
    far = CAMERA_FAR;
    m_targetPosition = CAMERA_DEF_TARGET_POSITION;
    m_LatitudeLongitude = glm::vec2(0.F);
}

const vec3 &LatitudeLongitudeCamera::getTargetPosition() const {
    return m_targetPosition;
}
