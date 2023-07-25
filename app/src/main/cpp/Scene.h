//
// Created by zoozo on 7/18/2023.
//

#ifndef LEARNGLES_SCENE_H
#define LEARNGLES_SCENE_H


class Scene {
public:
    virtual void init() = 0;
    virtual void resize(int width, int height) = 0;
    virtual void draw() = 0;
    virtual void destroy() = 0;
};


#endif //LEARNGLES_SCENE_H
