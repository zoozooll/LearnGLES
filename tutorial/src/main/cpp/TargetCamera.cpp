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
        m_targetRotation = m_targetRotation * rotation;

        viewDirty = true;
    }
}

void TargetCamera::roll(const float &angle) {
    quat rotation = glm::angleAxis(angle, vec3(0.f, 0.f, 1.f));
    m_targetRotation = m_targetRotation * rotation;
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
             glm::to_string(m_position).c_str(),
             glm::to_string(m_targetPosition).c_str(),
             glm::to_string(m_up).c_str());

        m_viewMatrix = glm::lookAt(m_position, m_targetPosition, m_up);
        m_front = glm::normalize(m_targetPosition - m_position);
        m_right = glm::normalize(glm::cross(m_front, m_up));
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

void TargetCamera::onSingleTouching(glm::vec2 prevPoint, glm::vec2 point) {
    // Screen coordinate system is up to down. And opengl coordinate system is down to up.
    vec2 distance(point.x - prevPoint.x, prevPoint.y - point.y);
    if (glm::any(glm::notEqual(distance, vec2(.0f)))) {
        vec2 perpendicular = glm::normalize(vec2(-distance.y, distance.x));
        float angle = glm::length(distance) * 0.01f / (float)M_PI;

        // Rotate around an axis in the camera's local plane (perpendicular to movement)
        quat rotation = glm::angleAxis(angle, vec3(perpendicular, 0.f));
        // Use post-multiplication to rotate around the local axes of the camera
        m_targetRotation = m_targetRotation * rotation;

        viewDirty = true;
    }
}

void TargetCamera::onDoubleTouching(glm::vec2 prevPoint0, glm::vec2 point0, glm::vec2 prevPoint1, glm::vec2 point1) {
    // 1. Zooming
    float prevDist = glm::distance(prevPoint0, prevPoint1);
    float currDist = glm::distance(point0, point1);
    if (prevDist > 0.0f && currDist > 0.0f) {
        float zoomFactor = prevDist / currDist;
        zoom(zoomFactor);
    }

    // 2. Rolling
    vec2 prevDir = prevPoint1 - prevPoint0;
    vec2 currDir = point1 - point0;
    if (glm::length(prevDir) > 0.0001f && glm::length(currDir) > 0.0001f) {
        prevDir = glm::normalize(prevDir);
        currDir = glm::normalize(currDir);
        float dot = glm::clamp(glm::dot(prevDir, currDir), -1.f, 1.f);
        float det = prevDir.x * currDir.y - prevDir.y * currDir.x;
        float angle = atan2(det, dot);
        if (glm::abs(angle) > 0.001f) {
            roll(angle);
        }
    }

    // 3. Moving (Panning)
    // Screen coordinate system is up to down. And opengl coordinate system is down to up.
    vec2 delta0(point0.x - prevPoint0.x, prevPoint0.y - point0.y);
    vec2 delta1(point1.x - prevPoint1.x, prevPoint1.y - point1.y);
    vec2 moveDelta = (delta0 + delta1) * 0.5f;
    // Panning: swipe right/up to move camera right/up relative to world (so target moves left/down)
    move(moveDelta * -0.01f);
}
