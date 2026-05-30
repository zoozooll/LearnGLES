//
// Created by zoozo on 7/20/2023.
//

#ifndef LEARNGLES_SHADER_H
#define LEARNGLES_SHADER_H

#include <string>
#include <GLES3/gl32.h>
#include <glm/glm.hpp>

#include "AssetHelper.h"

#include "logutil.h"
#include "logutil.h"

class Shader {
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath,
            const char* tessControlPath, const char* tessEvalPath);
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setUInt(const std::string &name, unsigned int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w);
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    void setTexture(const std::string &name, unsigned int textId, int texNum = 0u) const;


private:
    void checkCompileErrors(unsigned int shader, std::string type);
};


#endif //LEARNGLES_SHADER_H
