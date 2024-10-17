//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_DEPTHTESTINGSCENE_H
#define LEARNGLES_DEPTHTESTINGSCENE_H

#include "SceneTouchEvent.h"
#include "SceneCommand.h"
#include "BaseScene.h"



class Shader;

class DepthTestingScene : public BaseScene  {
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> sendCommand(std::map<std::string, std::any>) override;

private:

    Shader *shader = nullptr;
    unsigned int cubeVAO = 0U, cubeVBO = 0u;
    unsigned int planeVAO = 0U, planeVBO= 0U;
    unsigned int cubeTexture = 0u;
    unsigned int floorTexture = 0u;
    bool depthTesting = true;
};


#endif //LEARNGLES_DEPTHTESTINGSCENE_H
