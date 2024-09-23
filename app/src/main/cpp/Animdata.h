//
// Created by zoozo on 9/23/2024.
//

#ifndef LEARNGLES_ANIMDATA_H
#define LEARNGLES_ANIMDATA_H

#include<glm/glm.hpp>

struct BoneInfo
{
    /*id is index in finalBoneMatrices*/
    int id;

    /*offset matrix transforms vertex from model space to bone space*/
    glm::mat4 offset;

};

#endif //LEARNGLES_ANIMDATA_H
