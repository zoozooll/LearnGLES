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

    const glm::mat4 &getViewMatrix() const;

    const glm::mat4 &getProjectionMatrix() const;

    void start();

    void update();

    const glm::vec3& getPosition() const;

    glm::mat4 getVPMatrix() const;

    const glm::mat4 &getTargetTransform() const;

    float getRadius() const;

    void setTargetTransform(const glm::mat4 &targetTransform);

    glm::vec3 getTarget() const;

    float getNear() const;

    float getFar() const;
 
    const glm::mat4 &getProjectionDepthMatrix() const;

    float calculateScaleFactor(const float &distanceFromCamera, const float &desiredObjectSize) const;

    float getVdy() const;

    glm::vec3 getTargetPosition() const;

    float getFracRadius() const;

private:

    glm::mat4 m_targetTransform = glm::mat4(1.f);
    float m_radius = 8.f;
    float m_vdy = 75.f;
    float m_aspec = 0.f;
    float m_near = 0.f;
    float m_far = 0.f;

    float fracRadius = 0.F;

    glm::vec3 m_cameraPosition;

    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_projectionDepthMatrix;
    bool dirty = false;


    constexpr static const float CAMERA_FOVY_DEGREE = 60.f;
    constexpr static const float CAMERA_NEAR = 1.f;
    constexpr static const float CAMERA_FAR = 20.f;
    constexpr static const float CAMERA_DEF_RADIUS = 8.f;
    constexpr static const glm::vec3 CAMERA_DEF_TARGET_POSITION = glm::vec3(.0f, 2.f, .0f);
};


#endif //LEARNGLES_TARGETCAMERA_H
