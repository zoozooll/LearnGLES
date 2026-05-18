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
#include <algorithm>

namespace {
    struct FormatInfo {
        GLenum internalFormat;
        GLenum format;
    };

    FormatInfo getFormatInfo(int nrComponents, bool gammaCorrection) {
        if (nrComponents == 1) {
            return {static_cast<GLenum>(GL_R8), GL_RED};
        } else if (nrComponents == 3) {
            return {static_cast<GLenum>(gammaCorrection ? GL_SRGB8 : GL_RGB8), GL_RGB};
        } else if (nrComponents == 4) {
            return {static_cast<GLenum>(gammaCorrection ? GL_SRGB8_ALPHA8 : GL_RGBA8), GL_RGBA};
        }
        return {static_cast<GLenum>(GL_RGBA8), GL_RGBA};
    }

    int getMipMapLevels(int width, int height) {
        int levels = 0;
        int s = std::max(width, height);
        while (s > 0) {
            s >>= 1;
            levels++;
        }
        return levels;
    }
}

unsigned int loadTexture(char const * path, bool flip, bool gammaCorrection) {
    unsigned char *file_data = nullptr;
    size_t file_size = 0;

    if (!LoadDataFromAsset(path, reinterpret_cast<void **>(&file_data), &file_size)) {
        LOGE("Texture", "Texture failed to read from asset: %s", path);
        return 0;
    }

    stbi_set_flip_vertically_on_load(flip);
    int width, height, nrComponents;
    unsigned char *data = stbi_load_from_memory(file_data, file_size, &width, &height, &nrComponents, 0);
    free(file_data);

    if (!data) {
        LOGE("Texture", "Texture failed to decode at path: %s", path);
        return 0;
    }

    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    FormatInfo info = getFormatInfo(nrComponents, gammaCorrection);

    // Set unpack alignment for textures with non-4-byte aligned widths
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    int levels = getMipMapLevels(width, height);
    glTexStorage2D(GL_TEXTURE_2D, levels, info.internalFormat, width, height);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, info.format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    // Default wrapping and filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, info.format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, info.format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    return textureID;
}

unsigned int loadCubemap(std::vector<std::string> faces, bool gammaCorrection) {
    unsigned int textureID = 0;
    bool storageInitialized = false;

    // Set unpack alignment once
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char *file_data = nullptr;
        size_t file_size = 0;
        if (!LoadDataFromAsset(faces[i].c_str(), reinterpret_cast<void **>(&file_data), &file_size)) {
            LOGE("Texture", "Cubemap face failed to read from asset: %s", faces[i].c_str());
            continue;
        }

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(false);
        unsigned char *data = stbi_load_from_memory(file_data, file_size, &width, &height, &nrChannels, 0);
        free(file_data);

        if (!data) {
            LOGE("Texture", "Cubemap face failed to decode at path: %s", faces[i].c_str());
            continue;
        }

        if (!storageInitialized) {
            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
            FormatInfo info = getFormatInfo(nrChannels, gammaCorrection);
            // Cubemaps usually don't have mipmaps in these tutorials, but we could add them if needed.
            // Using 1 level for simplicity as per common cubemap usage in this project.
            glTexStorage2D(GL_TEXTURE_CUBE_MAP, 1, info.internalFormat, width, height);
            storageInitialized = true;
        }

        FormatInfo info = getFormatInfo(nrChannels, gammaCorrection);
        glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, 0, 0, width, height, info.format, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }

    if (storageInitialized) {
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    return textureID;
}

unsigned int genTexture(int width, int height, int channels, const void* data) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    FormatInfo info = getFormatInfo(channels, false);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    int levels = getMipMapLevels(width, height);
    glTexStorage2D(GL_TEXTURE_2D, levels, info.internalFormat, width, height);
    if (data) {
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, info.format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, info.format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, info.format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    return textureID;
}
