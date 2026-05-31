#ifndef LEARNGLES_BLENDINGSCENE_H
#define LEARNGLES_BLENDINGSCENE_H

#include "TutorialScene.h"

#include <GLES3/gl32.h>

#include <vector>

class Camera;

class Shader;

class BlendingScene : public TutorialScene {
public :
    BlendingScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~BlendingScene();

private:
    Camera* m_camera = nullptr;
    Shader* m_pShader = nullptr;
    unsigned int m_cubeVAO = 0u;
    unsigned int m_cubeVBO = 0u;
    unsigned int m_planeVAO = 0u;
    unsigned int m_planeVBO = 0u;
    unsigned int m_transparentVAO = 0u;
    unsigned int m_transparentVBO = 0u;

    unsigned int m_cubeTexture = 0u;
    unsigned int m_floorTexture = 0u;
    unsigned int m_transparentTexture = 0u;

    std::vector<glm::vec3> m_windows;

    //region Properties
    // Switch if blend is on.
    bool blendOn = true;

    // source blending factors. Value is one of GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR,
    // GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA.
    // GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA, and GL_ONE_MINUS_CONSTANT_ALPHA.
    GLenum srcFactor = GL_SRC_ALPHA;

    // destination blending factors. Value is one of GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR,
    // GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA.
    // GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA, and GL_ONE_MINUS_CONSTANT_ALPHA.
    GLenum dstFactor = GL_ONE_MINUS_SRC_ALPHA;

    // BlendEquation mode.
    // Value is one of GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_MIN, GL_MAX
    GLenum blendEquationMode = GL_FUNC_ADD;
    //endregion

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
    void parseBlendOnEvent(std::map<std::string, std::any> &event);
    void parseSrcFactorEvent(std::map<std::string, std::any> &event);
    void parseDstFactorEvent(std::map<std::string, std::any> &event);
    void parseBlendEquationEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_BLENDINGSCENE_H
