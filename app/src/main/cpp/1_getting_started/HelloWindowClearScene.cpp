//
// Created by zoozo on 7/18/2023.
//

#include "HelloWindowClearScene.h"

#include <GLES3/gl32.h>

void HelloWindowClearScene::init() {

}

void HelloWindowClearScene::resize(int width, int height) {
    glViewport(0, 0, width, height);
}

void HelloWindowClearScene::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void HelloWindowClearScene::destroy() {

}