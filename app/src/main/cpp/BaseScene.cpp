//
// Created by zoozo on 9/27/2024.
//

#include "BaseScene.h"

#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

#include "LatitudeLongitudeCamera.h"
#include "logutil.h"

using glm::vec2;
using std::vector;
using std::any;
using std::any_cast;
using glm::vec3;
using glm::vec4;

BaseScene::BaseScene() {
    camera = new LatitudeLongitudeCamera();
}

BaseScene::~BaseScene() {
    delete camera;
}

std::map<std::string, std::any> BaseScene::sendCommand(std::map<std::string, std::any> commands) {
    for (const auto& [key, value]: commands) {
        if ("camera_move" == key && value.type() == typeid(vector<float>)) {
            auto l_value = any_cast<vector<float>>(value);
            if (l_value.size() >= 2) {
                camera->move({l_value[0], -l_value[1]});
            }
        } else if ("camera_zoom" == key && value.type() == typeid(float)) {
            auto l_value = any_cast<float>(value);
            camera->zoom(l_value);
        } else if ("camera_yaw_pitch" == key && value.type() == typeid(vector<float>)) {
            auto l_value = any_cast<vector<float>>(value);
            if (l_value.size() >= 2) {
                camera->yawPitch({l_value[0] * -0.5F, l_value[1] * -0.1F});
            }
        } else if ("camera_radius" == key && value.type() == typeid(float)) {
            auto l_value = any_cast<float>(value);
            camera->setRadius(l_value);
        } else if ("camera_reset" == key) {
            camera->reset();
        }
    }
    return {};
}

void BaseScene::resize(int width, int height) {
    scrWidth = width;
    scrHeight = height;
    camera->setAspec((float) width / (float) height);
}

