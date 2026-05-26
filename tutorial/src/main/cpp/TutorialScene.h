//
// Created by zoozo on 7/18/2023.
//

#ifndef LEARNGLES_TUTORIALSCENE_H
#define LEARNGLES_TUTORIALSCENE_H

#include <map>
#include <string>
#include <any>
#include <glm/glm.hpp>

class TutorialScene {
public:
    virtual void init() = 0;

    virtual void resize(int width, int height) = 0;

    virtual void draw() = 0;

    virtual void destroy() = 0;

    virtual std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &);
};

#endif //LEARNGLES_TUTORIALSCENE_H
