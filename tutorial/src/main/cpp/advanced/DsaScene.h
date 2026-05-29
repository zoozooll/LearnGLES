#ifndef LEARNGLES_DSASCENE_H
#define LEARNGLES_DSASCENE_H

#include "TutorialScene.h"

class Camera;

class DsaScene : public TutorialScene {
public :
    DsaScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~DsaScene();

private:
    Camera* m_camera = nullptr;
    unsigned int m_shaderProgram = 0u;
    unsigned int m_vao = 0u, m_vbo = 0u, m_ebo = 0u;
    int m_width = 0;
    int m_height = 0;

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_DSASCENE_H
