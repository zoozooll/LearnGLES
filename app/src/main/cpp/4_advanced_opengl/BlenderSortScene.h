//
// Created by Aaron Lee on 2023/8/22.
//

#ifndef LEARNGLES_BLENDERSORTSCENE_H
#define LEARNGLES_BLENDERSORTSCENE_H

#include "BaseScene.h"

#include <vector>
#include <glm/glm.hpp>



class Shader;

class BlenderSortScene : public BaseScene {
private:


    unsigned int SCR_WIDTH = 0u;
    unsigned int SCR_HEIGHT = 0u;

    Shader *shader = nullptr;
    // cube VAO
    unsigned int cubeVAO = 0u, cubeVBO = 0u;
    // plane VAO
    unsigned int planeVAO = 0u, planeVBO = 0u;
    // transparent VAO
    unsigned int transparentVAO = 0u, transparentVBO = 0u;
    unsigned int cubeTexture = 0u;
    unsigned int floorTexture = 0u;
    unsigned int transparentTexture = 0u;

    std::vector<glm::vec3> vegetation
            {
                    glm::vec3(-1.5f, 0.0f, -0.48f),
                    glm::vec3( 1.5f, 0.0f, 0.51f),
                    glm::vec3( 0.0f, 0.0f, 0.7f),
                    glm::vec3(-0.3f, 0.0f, -2.3f),
                    glm::vec3 (0.5f, 0.0f, -0.6f)
            };

    // transparent window locations
    // --------------------------------
    std::vector<glm::vec3> windows
            {
                    glm::vec3(-1.5f, 0.0f, -0.48f),
                    glm::vec3( 1.5f, 0.0f, 0.51f),
                    glm::vec3( 0.0f, 0.0f, 0.7f),
                    glm::vec3(-0.3f, 0.0f, -2.3f),
                    glm::vec3( 0.5f, 0.0f, -0.6f)
            };
public:
    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;
};


#endif //LEARNGLES_BLENDERSORTSCENE_H
