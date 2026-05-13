//
// Created by Aaron Lee on 2023/10/31.
//

#include "TargetCamera.h"

#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/quaternion.hpp>

#include "logutil.h"

using glm::vec2;
using glm::vec3;
using glm::mat3;
using glm::mat4;
using glm::quat;
using glm::radians;
using glm::perspective;

void TargetCamera::move(const vec2 &move) {
    vec3 right = m_targetRotation * vec3(1.f, 0.f, 0.f);
    vec3 up    = m_targetRotation * vec3(0.f, 1.f, 0.f);

    m_targetPosition += move.x * right + move.y * up;
    viewDirty = true;
}

void TargetCamera::zoom(const float &zoom) {
    m_radius *= zoom;
    m_radius = fmin(fmax(2.f, m_radius), 50.f);
    viewDirty = true;
}

void TargetCamera::yawPitch(const vec2 &director) {
    if (glm::any(glm::notEqual(director, vec2(.0f)))){
        vec2 perpendicular = glm::normalize(vec2(-director.y, director.x));
        float angle = glm::length(director) * 0.01f / (float)M_PI;

        // Rotate around an axis in the camera's local plane (perpendicular to movement)
        quat rotation = glm::angleAxis(angle, vec3(perpendicular, 0.f));
        m_targetRotation = rotation * m_targetRotation;

        viewDirty = true;
    }
}

void TargetCamera::roll(const float &angle) {
    quat rotation = glm::angleAxis(angle, vec3(0.f, 0.f, 1.f));
    m_targetRotation = rotation * m_targetRotation;
    viewDirty = true;
}

void TargetCamera::setRadius(float mRadius) {
    m_radius = mRadius;
    viewDirty = true;
}

mat4 TargetCamera::getTargetTransform() const {
    mat4 translation = glm::translate(mat4(1.f), m_targetPosition);
    mat4 rotation = glm::toMat4(m_targetRotation);
    return translation * rotation;
}

float TargetCamera::getRadius() const {
    return m_radius;
}

void TargetCamera::setTargetTransform(const mat4 &targetTransform) {
    m_targetPosition = vec3(targetTransform[3]);
    // Extract rotation from matrix (assuming no scale)
    m_targetRotation = glm::quat_cast(targetTransform);
    viewDirty = true;
}

void TargetCamera::setTargetPosition(const vec3 &targetPosition) {
    m_targetPosition = targetPosition;
    viewDirty = true;
}

void TargetCamera::setTargetRotation(const quat &targetRotation) {
    m_targetRotation = targetRotation;
    viewDirty = true;
}

const quat &TargetCamera::getTargetRotation() const {
    return m_targetRotation;
}

void TargetCamera::update() {
    if (viewDirty) {
        vec3 forward = m_targetRotation * vec3(0.f, 0.f, 1.f);
        m_up = m_targetRotation * vec3(0.f, 1.f, 0.f);

        m_position = m_targetPosition + forward * m_radius;

        LOGI(__FILE_NAME__, "update cameraPosition: %s, target: %s, up: %s",
             glm::to_string(m_position).c_str(), glm::to_string(m_targetPosition).c_str(), glm::to_string(m_up).c_str());

        m_viewMatrix = glm::lookAt(m_position, m_targetPosition, m_up);
        viewDirty = false;
    }
    if (projectionDirty) {
        m_projectionMatrix = glm::perspective(glm::radians(m_vdy), m_aspec, m_near, m_far);
        projectionDirty = false;
    }
}

float TargetCamera::calculateScaleFactor(const float &distanceFromCamera, const float &desiredObjectSize) const {
    float viewSpaceSize = 2.0f * distanceFromCamera * tan(glm::radians(m_vdy / 2.0f));
    float screenWidth = viewSpaceSize / m_aspec;
    return desiredObjectSize / screenWidth;
}

void TargetCamera::reset() {
    m_targetPosition = vec3(0.f);
    m_targetRotation = quat(1.f, 0.f, 0.f, 0.f);
    m_radius = CAMERA_DEF_RADIUS;
    m_vdy = CAMERA_FOVY_DEGREE;
    m_near = CAMERA_NEAR;
    m_far = CAMERA_FAR;
    viewDirty = true;
    projectionDirty = true;
}
