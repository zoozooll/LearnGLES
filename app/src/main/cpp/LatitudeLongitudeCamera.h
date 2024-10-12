//
// Created by zoozo on 10/8/2024.
//

#ifndef LEARNGLES_LATITUDELONGITUDECAMERA_H
#define LEARNGLES_LATITUDELONGITUDECAMERA_H

#include <glm/glm.hpp>

class LatitudeLongitudeCamera {
private:
    constexpr static const float CAMERA_FOVY_DEGREE = 60.f;
    constexpr static const float CAMERA_NEAR = 1.f;
    constexpr static const float CAMERA_FAR = 15.f;
    constexpr static const float CAMERA_DEF_RADIUS = 8.f;
    constexpr static const glm::vec3 CAMERA_DEF_UP = glm::vec3(.0f, 1.f, .0f);
    constexpr static const glm::vec3 CAMERA_DEF_TARGET_POSITION = glm::vec3(.0f, 0.f, .0f);

    glm::vec3 m_targetPosition = CAMERA_DEF_TARGET_POSITION;
    glm::vec2 m_LatitudeLongitude = glm::vec2(0.F);
    float radius = CAMERA_DEF_RADIUS;
    float vdy = CAMERA_FOVY_DEGREE;
    float aspec = 0.f;
    float near = CAMERA_NEAR;
    float far = CAMERA_FAR;

    glm::vec3 m_cameraPosition;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
    bool dirty = false;
public:
    void move(const glm::vec2 &screen_move);

    void zoom(const float &zoom);

    void yawPitch(const glm::vec2 &director);

    void setRadius(float mRadius);

    void setVdy(float vdy);

    void setAspec(float aspec);

    void setNear(float near);

    void setFar(float far);

    [[nodiscard]] const glm::mat4 &getViewMatrix() const;

    [[nodiscard]] const glm::mat4 &getProjectionMatrix() const;

    void start();

    void update();

    [[nodiscard]] const glm::vec3& getPosition() const;

    [[nodiscard]] glm::mat4 getVPMatrix() const;

    [[nodiscard]] float getRadius() const;

    [[nodiscard]] float getNear() const;

    [[nodiscard]] float getFar() const;

    [[nodiscard]] float getVdy() const;

    [[nodiscard]] const glm::vec3 &getTargetPosition() const;

    void reset();
};


#endif //LEARNGLES_LATITUDELONGITUDECAMERA_H
