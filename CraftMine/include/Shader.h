#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <filesystem>
#include <system_error>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader
{
private: 
    unsigned int finalShader;

    unsigned int initShaderStep(const std::string& codePath, GLenum shaderType);
    unsigned int compileShaderStep(const std::string& shaderCode, GLenum shaderType);
    void assertLinking();
    std::string getShaderCode(const std::string& shaderPath);

public:
    unsigned int ID;

    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    Shader(const std::string& vertexPath, const std::string& geometryPath, const std::string& fragmentPath);
    Shader(const Shader&) = delete;

    Shader& operator = (const Shader&) = delete;

    inline unsigned int getId() { return finalShader; }

    void use() const;
    void sendVec2(const std::string& name, const glm::vec2& value) const;
    void sendVec3(const std::string& name, const glm::vec3& value) const;
    void sendMat4(const std::string& name, const glm::mat4& value) const;
    void sendMat4(const std::string& name, const std::vector<glm::mat4>& value) const;
    void sendFloat(const std::string& name, float value) const;
    void sendInt(const std::string& name, int value) const;
};
