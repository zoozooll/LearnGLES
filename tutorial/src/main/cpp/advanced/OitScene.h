#ifndef LEARNGLES_OITSCENE_H
#define LEARNGLES_OITSCENE_H

#include "TutorialScene.h"

class Camera;
class Shader;

class OitScene : public TutorialScene {
public :
    OitScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    virtual ~OitScene();

private:
    Camera* camera = nullptr;
    Shader* solidShader = nullptr;;
    Shader* transparentShader = nullptr;;
    Shader* compositeShader = nullptr;;
    Shader* screenShader = nullptr;;

    unsigned int quadVAO = 0u, quadVBO = 0u;
    unsigned int opaqueFBO = 0u, transparentFBO = 0u;
    unsigned int opaqueTexture = 0u;
    unsigned int depthTexture = 0u;
    unsigned int accumTexture = 0u;
    unsigned int revealTexture = 0u;

    int m_width = 0;
    int m_height = 0;

    glm::mat4 calculate_model_matrix(const glm::vec3& position,
            const glm::vec3& rotation = glm::vec3(0.0f),
            const glm::vec3& scale = glm::vec3(1.0f));
};

#endif //LEARNGLES_OITSCENE_H
