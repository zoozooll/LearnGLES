//
// Created by zoozo on 2026/5/11.
//

#ifndef LEARNGLES_BASICGLESSCENE_H
#define LEARNGLES_BASICGLESSCENE_H

#include "TutorialScene.h"

class Camera;

class Shader;

class BasicGlesScene : public TutorialScene {
public:
    BasicGlesScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~BasicGlesScene();

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

private:
    Camera *camera = nullptr;

    Shader* m_pShader = nullptr;
    unsigned int VBO = 0u, VAO = 0u;
    unsigned int texture1 = 0u, texture2 = 0u;
    int m_width = 0;
    int m_height = 0;

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};


#endif //LEARNGLES_BASICGLESSCENE_H
