//
// Created by huion on 2023/10/31.
//

#ifndef LEARNGLES_TARGETCAMERA_H
#define LEARNGLES_TARGETCAMERA_H

#include <glm/glm.hpp>

using namespace glm;

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

    const mat4 &getViewMatrix() const;

    const mat4 &getProjectionMatrix() const;

    void updateCameraMatrix();
private:

    mat4 m_targetTransform = mat4(1.f);
    float m_radius = 8.f;
    float m_vdy = 75.f;
    float m_aspec = 0.f;
    float m_near = 0.f;
    float m_far = 0.f;

    mat4 m_viewMatrix;
    mat4 m_projectionMatrix;
};


#endif //LEARNGLES_TARGETCAMERA_H
