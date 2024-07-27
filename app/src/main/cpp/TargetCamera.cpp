//
// Created by Aaron Lee on 2023/10/31.
//

#include "TargetCamera.h"

#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

#include "logutil.h"

using glm::vec2;
using glm::vec3;
using glm::mat3;
using glm::mat4;
using glm::radians;
using glm::perspective;

void TargetCamera::start() {

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
}

void TargetCamera::zoom(const float &zoom) {
    m_radius *= zoom;
    m_radius = fmin(fmax(2.f, m_radius), 50.f);
}

void TargetCamera::yawPitch(const vec2 &director) {
    if (glm::any(glm::notEqual(director, vec2(.0f)))){
	    glm::mat4 l_matrix(1.0f);
	    glm::vec2 perpendicular = glm::normalize(glm::vec2(-director.y, director.x));
	    auto angle = glm::length(director) * 0.01f / M_PI;
	    l_matrix = glm::rotate(l_matrix, float(angle), glm::vec3(perpendicular, 0.f) );
	    m_targetTransform = l_matrix * m_targetTransform;
    }
}

void TargetCamera::roll(const float &angle) {
    glm::mat4 l_matrix = glm::rotate(glm::mat4(1.f), angle, glm::vec3(0.f, 0.f, 1.f));
    m_targetTransform = l_matrix * m_targetTransform;
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

const vec3 &TargetCamera::getPosition() const {
    return m_cameraPosition;
}

mat4 TargetCamera::getVPMatrix() const {
    return m_projectionMatrix * m_viewMatrix;
}

const mat4 &TargetCamera::getTargetTransform() const {
    return m_targetTransform;
}

float TargetCamera::getRadius() const {
    return m_radius;
}

void TargetCamera::setTargetTransform(const mat4 &targetTransform) {
    m_targetTransform = targetTransform;
}

void TargetCamera::update() {
    vec3 target(m_targetTransform[3][0] / m_targetTransform[3][3], m_targetTransform[3][1] / m_targetTransform[3][3],
                m_targetTransform[3][2] / m_targetTransform[3][3]);
    vec3 right   (m_targetTransform[0][0], m_targetTransform[1][0], m_targetTransform[2][0]);
    vec3 up      (m_targetTransform[0][1], m_targetTransform[1][1], m_targetTransform[2][1]);
    vec3 forward (m_targetTransform[0][2], m_targetTransform[1][2], m_targetTransform[2][2]);

//    vec3 right = mat3(m_targetTransform) * RIGHT;
//    vec3 up = mat3(m_targetTransform) * UP;
//    vec3 forward = mat3(m_targetTransform) * FORWARD;
    right = normalize(right);
    up = normalize(up);
    forward = normalize(forward);

    // The functional is r1 * tan(theta_one/2.0) = r2 * tan(theta_two/2.0). So r2 / r1 = tan(theta_one/2.0) / tan(theta_two/2.0)
    fracRadius = tan(glm::radians(60.F) * .5F) / tan(glm::radians(m_vdy) * .5f);

    m_cameraPosition = target + forward * m_radius * fracRadius;
    LOGI(__FILE_NAME__, "start cameraPosition: %s, target: %s, up: %s",
         to_string(m_cameraPosition).c_str(),  to_string(target).c_str(), to_string(up).c_str());
    m_viewMatrix = lookAt(m_cameraPosition, target, up);
    m_projectionMatrix = glm::perspective(glm::radians(m_vdy), m_aspec, m_near, m_far);
    m_projectionDepthMatrix = glm::perspective(glm::radians(m_vdy), m_aspec, 1.f, 25.f);
}

vec3 TargetCamera::getTarget() const {
    return {m_targetTransform[3][0] / m_targetTransform[3][3], m_targetTransform[3][1] / m_targetTransform[3][3],
                     m_targetTransform[3][2] / m_targetTransform[3][3]};
}

float TargetCamera::getNear() const {
    return m_near;
}

float TargetCamera::getFar() const {
    return m_far;
}

const mat4 &TargetCamera::getProjectionDepthMatrix() const {
    return m_projectionDepthMatrix;
}

float TargetCamera::calculateScaleFactor(const float &distanceFromCamera, const float &desiredObjectSize) const {
    float viewSpaceSize = 2.0f * distanceFromCamera * tan(glm::radians(m_vdy / 2.0f));
    float screenWidth = viewSpaceSize / m_aspec;
    return desiredObjectSize / screenWidth;
}

float TargetCamera::getVdy() const {
    return m_vdy;
}

glm::vec3 TargetCamera::getTargetPosition() const {
    return vec3(m_targetTransform[3][0] / m_targetTransform[3][3], m_targetTransform[3][1] / m_targetTransform[3][3],
                       m_targetTransform[3][2] / m_targetTransform[3][3]);;
}

float TargetCamera::getFracRadius() const {
    return fracRadius;
}
