//
// Created by Aaron Lee on 2023/4/10.
//

#ifndef OBJECT3DDEMO_MOVABLECAMERA_H
#define OBJECT3DDEMO_MOVABLECAMERA_H
#include <glm/glm.hpp>

//using namespace glm;

class MovableCamera {
private:
    float m_radius;  //半径
    float m_longitude;  // 经度
    float m_latitude; // 纬度
    glm::mat4 viewMatrix;
    glm::vec3 position;
    void calculateViewTransform();

public:
    void zoom(float radius);

    void rotateHorizontal(float degrees);

    void rotateVirtual(float degrees);

    void setRadius(float radius);

    void setLongitude(float longitude);

    void setLatitude(float latitude);

    const glm::mat4 &GetViewMatrix();

    const glm::vec3 &getPosition() const;
};


#endif //OBJECT3DDEMO_MOVABLECAMERA_H
