#ifndef LEARNGLES_DEBUGGINGSCENE_H
#define LEARNGLES_DEBUGGINGSCENE_H

#include "Scene.h"

#include <GLES3/gl32.h>

class Shader;
class Camera;

class DebuggingScene : public Scene {
public :
    DebuggingScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~DebuggingScene();

private:
    Camera* m_camera = nullptr;
    Shader* m_pShader = nullptr;
    unsigned int m_cubeVAO = 0u, m_cubeVBO = 0u;
    unsigned int m_texture = 0u;
    int m_width = 0;
    int m_height = 0;

    static void glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity,
        GLsizei length, const char *message, const void *userParam);
};

#endif //LEARNGLES_DEBUGGINGSCENE_H
