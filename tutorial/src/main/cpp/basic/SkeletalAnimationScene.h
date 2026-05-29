#ifndef LEARNGLES_SKELETALANIMATIONSCENE_H
#define LEARNGLES_SKELETALANIMATIONSCENE_H

#include "TutorialScene.h"

class Camera;
class Shader;
class AnimatedModel;
class Animation;
class Animator;

class SkeletalAnimationScene : public TutorialScene {
public :
    SkeletalAnimationScene();

    void init() override;

    void resize(int width, int height) override;

    void draw() override;

    void destroy() override;

    std::map<std::string, std::any> propertyEvent(std::map<std::string, std::any> &map) override;

    virtual ~SkeletalAnimationScene();

private:
    Camera* m_camera = nullptr;
    Shader* ourShader = nullptr;
    AnimatedModel* ourModel = nullptr;
    Animation* danceAnimation = nullptr;
    Animator* animator = nullptr;

    int m_width = 0;
    int m_height = 0;
    float deltaTime = 0.f;
    float lastFrame = 0.f;

    void parseTargetCameraEvent(std::map<std::string, std::any> &event);
};

#endif //LEARNGLES_SKELETALANIMATIONSCENE_H
