//
// Created by zoozo on 9/23/2024.
//

#ifndef LEARNGLES_ANIMATION_H
#define LEARNGLES_ANIMATION_H


#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <Bone.h>
#include <functional>
#include <Animdata.h>
#include "AnimatedModel.h"

struct AssimpNodeData
{
    glm::mat4 transformation;
    std::string name;
    int childrenCount;
    std::vector<AssimpNodeData> children;
};

class Animation
{
public:
    Animation() = default;

    Animation(const std::string& animationPath, AnimatedModel* model);

    virtual ~Animation();

    Bone* FindBone(const std::string& name);

    float GetTicksPerSecond();
    float GetDuration();
    const AssimpNodeData& GetRootNode();
    const std::map<std::string,BoneInfo>& GetBoneIDMap();
private:
    void ReadMissingBones(const aiAnimation* animation, AnimatedModel& model);

    void ReadHierarchyData(AssimpNodeData& dest, const aiNode* src);

    float m_Duration = 0.F;
    int m_TicksPerSecond = 0;
    std::vector<Bone> m_Bones;
    AssimpNodeData m_RootNode;
    std::map<std::string, BoneInfo> m_BoneInfoMap;
};


#endif //LEARNGLES_ANIMATION_H
