//
// Created by zoozo on 9/27/2024.
//

#ifndef LEARNGLES_BASESCENE_H
#define LEARNGLES_BASESCENE_H

#include "Scene.h"
#include "SceneCommand.h"
#include "LatitudeLongitudeCamera.h"

class BaseScene : public Scene, public SceneCommand {
protected:
    LatitudeLongitudeCamera *camera = nullptr;
    int scrWidth = 0;
    int scrHeight = 0;

public:
    BaseScene();

    virtual ~BaseScene();

    virtual void resize(int width, int height) override;

    std::map<std::string, std::any> sendCommand(std::map<std::string, std::any> map) override;
};


#endif //LEARNGLES_BASESCENE_H
