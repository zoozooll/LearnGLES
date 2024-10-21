//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_STENCILTESTINGSCENE_H
#define LEARNGLES_STENCILTESTINGSCENE_H

#include "BaseScene.h"

#include <GLES3/gl32.h>


class Shader;

class StencilTestingScene : public BaseScene {
private:
    Shader *shader = nullptr;
    Shader *shaderSingleColor = nullptr;

    unsigned int cubeVAO = 0U, cubeVBO = 0U;
    unsigned int planeVAO= 0U, planeVBO = 0U;
    unsigned int cubeTexture = 0U;
    unsigned int floorTexture = 0U;

    bool stencilTesting = true;
    int stencilFunc = GL_ALWAYS;
    int stencilOpSfail = GL_KEEP;
    int stencilOpDfail = GL_KEEP;
    int stencilDppass = GL_REPLACE;

public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> sendCommand(std::map<std::string, std::any> commands) override;

    void setStencilTest() const;

    void setStencilTesting(bool stencilTesting);

    void setStencilFunc(int stencilFunc);

    void setStencilOpSfail(int stencilOpSfail);

    void setStencilOpDfail(int stencilOpDfail);

    void setStencilDppass(int stencilDppass);
};


#endif //LEARNGLES_STENCILTESTINGSCENE_H
