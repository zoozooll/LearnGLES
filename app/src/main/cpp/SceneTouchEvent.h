//
// Created by huion on 2023/10/18.
//

#ifndef LEARNGLES_SCENETOUCHEVENT_H
#define LEARNGLES_SCENETOUCHEVENT_H

#include <glm/glm.hpp>

class SceneTouchEvent {
public:
    virtual void move(const glm::vec2 &start_pivot, const glm::vec2 &end_pivot);

    virtual void scale(const float &scale);

    virtual void yawPitch(const glm::vec2 &director);

    virtual void roll(const float &angle);

    virtual void onSingleClick(const glm:: vec2 point);

    virtual void onDoubleClick(const glm:: vec2 point);

    virtual void onLongPress(const glm:: vec2 point);
};


#endif //LEARNGLES_SCENETOUCHEVENT_H
