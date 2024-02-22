//
// Created by Aaron Lee on 2023/10/31.
//

#ifndef LEARNGLES_TARGETCAMERA_H
#define LEARNGLES_TARGETCAMERA_H

#include <glm/glm.hpp>

//using namespace glm;

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

    void updateCameraMatrix();

    const glm::vec3 &getCameraPosition() const;

private:

    glm::mat4 m_targetTransform = glm::mat4(1.f);
    float m_radius = 8.f;
    float m_vdy = 75.f;
    float m_aspec = 0.f;
    float m_near = 0.f;
    float m_far = 0.f;

    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
    glm::vec3 cameraPosition;
};


#endif //LEARNGLES_TARGETCAMERA_H
