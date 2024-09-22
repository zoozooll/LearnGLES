//
// Created by zoozo on 8/21/2023.
//

#ifndef LEARNGLES_TEXTURE_H
#define LEARNGLES_TEXTURE_H

#include <vector>
#include <string>

unsigned int loadTexture(char const * path);

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path, bool gammaCorrection);

unsigned int loadCubemap(std::vector<std::string> faces);

#endif //LEARNGLES_TEXTURE_H
