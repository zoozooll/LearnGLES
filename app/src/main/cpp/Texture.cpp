//
// Created by zoozo on 8/21/2023.
//

#include "Texture.h"
#include <GLES3/gl32.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl3platform.h>
#include <stb_image.h>
#include "AssetHelper.h"
#include "logutil.h"
#include <cstdlib>

unsigned int loadTexture(char const * path)
{
    unsigned int textureID = 0u;
    unsigned char *file_data = nullptr;
    size_t file_size = 0;

    if (!LoadDataFromAsset(path, reinterpret_cast<void **>(&file_data), &file_size))
    {
        LOGE("Texture", "Texture failed to read from asset: %s", path);
        free(file_data); // Safe to call on nullptr
        return 0;
    }

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load_from_memory(file_data, file_size, &width, &height, &nrComponents, 0);

    // Once decoded by stb_image, the raw file data is no longer needed
    free(file_data);

    if (data)
    {
        GLint internalFormat;
        GLenum format = 0;
        if (nrComponents == 1) {
            internalFormat = GL_R8;
            format = GL_RED;
        }
        else if (nrComponents == 3) {
            internalFormat = GL_RGB;
            format = GL_RGB;
        }
        else if (nrComponents == 4) {
            internalFormat = GL_RGBA;
            format = GL_RGBA;
        }
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders for RGBA.
        // Due to interpolation it takes texels from next repeat if set to REPEAT.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
    }
    else
    {
        LOGE("Texture", "Texture failed to decode at path: %s", path);
    }

    return textureID;
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path, bool gammaCorrection)
{
    unsigned int textureID = 0u;
    unsigned char *file_data = nullptr;
    size_t file_size = 0;

    if (!LoadDataFromAsset(path, reinterpret_cast<void **>(&file_data), &file_size))
    {
        LOGE("Texture", "Texture failed to read from asset: %s", path);
        free(file_data);
        return 0;
    }

    int width, height, nrComponents;
    unsigned char *data = stbi_load_from_memory(file_data, file_size, &width, &height, &nrComponents, 0);
    free(file_data);

    if (data)
    {
        GLenum internalFormat;
        GLenum dataFormat;
        if (nrComponents == 1)
        {
            internalFormat = GL_R8;
            dataFormat = GL_RED;
        }
        else if (nrComponents == 3)
        {
            internalFormat = gammaCorrection ? GL_SRGB8 : GL_RGB;
            dataFormat = GL_RGB;
        }
        else if (nrComponents == 4)
        {
            internalFormat = gammaCorrection ? GL_SRGB8_ALPHA8 : GL_RGBA;
            dataFormat = GL_RGBA;
        }

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        LOGE("Texture", "Texture failed to decode at path: %s", path);
    }

    return textureID;
}


// loads a cubemap texture from 6 individual texture faces
// order:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front)
// -Z (back)
// -------------------------------------------------------
unsigned int loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID = 0u;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *file_data = nullptr;
        size_t file_size = 0;
        if (LoadDataFromAsset(faces[i].c_str(), reinterpret_cast<void **>(&file_data), &file_size))
        {
            unsigned char *data = stbi_load_from_memory(file_data, file_size, &width, &height, &nrChannels, 0);
            free(file_data);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                stbi_image_free(data);
            }
            else
            {
                LOGE("Texture", "Cubemap face failed to decode at path: %s", faces[i].c_str());
            }
        }
        else
        {
            LOGE("Texture", "Cubemap face failed to read from asset: %s", faces[i].c_str());
            free(file_data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}
