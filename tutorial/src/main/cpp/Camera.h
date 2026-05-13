//
// Created by Aaron Lee on 2023/08/03.
//

#ifndef LEARNGLES_CAMERA_H
#define LEARNGLES_CAMERA_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:

    virtual ~Camera() = default;

    virtual void setVdy(float mVdy);

    virtual void setAspec(float mAspec);

    virtual void setNear(float mNear);

    virtual void setFar(float mFar);

    virtual const glm::mat4 &getViewMatrix() const;

    virtual const glm::mat4 &getProjectionMatrix() const;

    virtual void start();

    virtual void update();

    virtual void setPosition(const glm::vec3 &position);

    virtual const glm::vec3& getPosition() const;

    virtual glm::mat4 getVPMatrix() const;

    virtual float getNear() const;

    virtual float getFar() const;

    virtual float getVdy() const;

    virtual const glm::vec3 &getTargetPosition() const;

    virtual void setTargetPosition(const glm::vec3 &targetPosition);

    virtual const glm::vec3 &getUp() const;

    virtual void setUp(const glm::vec3 &up);

    virtual void reset();

protected:
    float m_vdy = CAMERA_FOVY_DEGREE;
    float m_aspec = 0.f;
    float m_near = CAMERA_NEAR;
    float m_far = CAMERA_FAR;

    glm::vec3 m_position;
    glm::vec3 m_targetPosition;
    glm::vec3 m_up;

    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
    bool viewDirty = false;
    bool projectionDirty = false;

    constexpr static const float CAMERA_FOVY_DEGREE = 60.f;
    constexpr static const float CAMERA_NEAR = 0.1f;
    constexpr static const float CAMERA_FAR = 100.f;
    constexpr static const glm::vec3 CAMERA_DEF_TARGET_POSITION = glm::vec3(.0f, 0.f, .0f);
};
#endif //LEARNGLES_CAMERA_H
