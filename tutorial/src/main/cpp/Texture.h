//
// Created by zoozo on 8/21/2023.
//

#ifndef LEARNGLES_TEXTURE_H
#define LEARNGLES_TEXTURE_H

#include <vector>
#include <string>

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path, bool flip = true, bool gammaCorrection = false);

// loads a cubemap texture from 6 individual texture faces
// -------------------------------------------------------
unsigned int loadCubemap(std::vector<std::string> faces, bool gammaCorrection = false);

unsigned int genTexture(int width, int height, int channels, const void* data = nullptr);

#endif //LEARNGLES_TEXTURE_H
