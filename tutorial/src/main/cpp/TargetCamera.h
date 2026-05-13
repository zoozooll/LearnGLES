//
// Created by Aaron Lee on 2023/10/31.
//

#ifndef LEARNGLES_TARGETCAMERA_H
#define LEARNGLES_TARGETCAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Camera.h"

class TargetCamera : public Camera {
public:
    void move(const glm::vec2 &move);

    void zoom(const float &zoom);

    void yawPitch(const glm::vec2 &director);

    void roll(const float &angle);

    void setRadius(float mRadius);

    void update() override;

    glm::mat4 getTargetTransform() const;

    float getRadius() const;

    void setTargetTransform(const glm::mat4 &targetTransform);

    void setTargetPosition(const glm::vec3 &targetPosition) override;

    void setTargetRotation(const glm::quat &targetRotation);

    const glm::quat &getTargetRotation() const;

    float calculateScaleFactor(const float &distanceFromCamera, const float &desiredObjectSize) const;

    float getFracRadius() const;

    void reset() override;

protected:
    glm::quat m_targetRotation = glm::quat(1.f, 0.f, 0.f, 0.f);
    float m_radius = CAMERA_DEF_RADIUS;

    constexpr static const float CAMERA_FOVY_DEGREE = 60.f;
    constexpr static const float CAMERA_NEAR = 0.1f;
    constexpr static const float CAMERA_FAR = 100.f;
    constexpr static const float CAMERA_DEF_RADIUS = 8.f;
    constexpr static const glm::vec3 CAMERA_DEF_TARGET_POSITION = glm::vec3(.0f, 0.f, .0f);
};


#endif //LEARNGLES_TARGETCAMERA_H
