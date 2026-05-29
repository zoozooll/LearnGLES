#ifndef LEARNGLES_TEXTRENDERINGSCENE_H
#define LEARNGLES_TEXTRENDERINGSCENE_H

#include "TutorialScene.h"

#include <map>

class Shader;

class Camera;

struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};


class TextRenderingScene : public TutorialScene {
public :
    TextRenderingScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~TextRenderingScene();

private:
    Camera* m_camera = nullptr;
    Shader* m_pShader = nullptr;
    std::map<char, Character> Characters;
    unsigned int m_VAO = 0u, m_VBO = 0u;
    int m_width = 0;
    int m_height = 0;

    void RenderText(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color);
    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_TEXTRENDERINGSCENE_H
