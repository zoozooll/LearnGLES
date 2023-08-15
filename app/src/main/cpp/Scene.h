//
// Created by zoozo on 7/18/2023.
//

#ifndef LEARNGLES_SCENE_H
#define LEARNGLES_SCENE_H

#include "glm/glm.hpp"

class Scene {
public:
    virtual void init() = 0;
    virtual void resize(int width, int height) = 0;
    virtual void draw() = 0;
    virtual void destroy() = 0;

    virtual void move(const glm::vec2 &start_pivot, const glm::vec2 &end_pivot);

    virtual void scale(const float &scale);

    virtual void yawPitch(const glm::vec2 &director);

    virtual void roll(const float &angle);
};


#endif //LEARNGLES_SCENE_H
