//
// Created by Aaron Lee on 2023/10/31.
//

#ifndef LEARNGLES_TARGETCAMERA_H
#define LEARNGLES_TARGETCAMERA_H

#include <glm/glm.hpp>

class TargetCamera {
public:
    void move(const glm::vec2 &move);

    void zoom(const float &zoom);

    void yawPitch(const glm::vec2 &director);

    void roll(const float &angle);

    void setRadius(float mRadius);

    void setVdy(float mVdy);

    void setAspec(float mAspec);

    void setNear(float mNear);

    void setFar(float mFar);

    [[nodiscard]] const glm::mat4 &getViewMatrix() const;

    [[nodiscard]] const glm::mat4 &getProjectionMatrix() const;

    void start();

    void update();

    [[nodiscard]] const glm::vec3& getPosition() const;

    [[nodiscard]] glm::mat4 getVPMatrix() const;

    [[nodiscard]] const glm::mat4 &getTargetTransform() const;

    [[nodiscard]] float getRadius() const;

    void setTargetTransform(const glm::mat4 &targetTransform);

    [[nodiscard]] glm::vec3 getTarget() const;

    [[nodiscard]] float getNear() const;

    [[nodiscard]] float getFar() const;

    [[nodiscard]] float calculateScaleFactor(const float &distanceFromCamera, const float &desiredObjectSize) const;

    [[nodiscard]] float getVdy() const;

    [[nodiscard]] glm::vec3 getTargetPosition() const;

    [[nodiscard]] float getFracRadius() const;

    void reset();

private:

    glm::mat4 m_targetTransform = glm::mat4(1.f);
    float m_radius = CAMERA_DEF_RADIUS;
    float m_vdy = CAMERA_FOVY_DEGREE;
    float m_aspec = 0.f;
    float m_near = CAMERA_NEAR;
    float m_far = CAMERA_FAR;

    float fracRadius = 0.F;

    glm::vec3 m_cameraPosition;

    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
    bool dirty = false;

    constexpr static const float CAMERA_FOVY_DEGREE = 60.f;
    constexpr static const float CAMERA_NEAR = 1.f;
    constexpr static const float CAMERA_FAR = 15.f;
    constexpr static const float CAMERA_DEF_RADIUS = 8.f;
    constexpr static const glm::vec3 CAMERA_DEF_TARGET_POSITION = glm::vec3(.0f, 0.f, .0f);
};


#endif //LEARNGLES_TARGETCAMERA_H
