//
// Created by Aaron Lee on 2024/3/9.
//

#ifndef LEARNGLES_SCENECOMMAND_H
#define LEARNGLES_SCENECOMMAND_H

#include <string>
#include <map>
#include <any>

class SceneCommand {
public:
    virtual std::map<std::string, std::any> sendCommand(std::map<std::string, std::any>) = 0;
};


#endif //LEARNGLES_SCENECOMMAND_H
