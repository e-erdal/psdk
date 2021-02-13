//
// Created on February 13th 2021 by loanselot1.
//
// Purpose: Main shader handler of SDK.
//

#pragma once

#include "pch.h"
#include <unordered_map>

class Shader {
public:
    Shader(const std::string &path);
    Shader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc);
    ~Shader();

    void Bind();
    void Unbind();

    void SetInt(const std::string &name, int value);
    void SetIntArray(const std::string &name, int *values, uint32_t count);
    void SetFloat(const std::string &name, float value);
    void SetVec2(const std::string &name, const glm::vec2 &value);
    void SetVec3(const std::string &name, const glm::vec3 &value);
    void SetVec4(const std::string &name, const glm::vec4 &value);
    void SetMat4(const std::string &name, const glm::mat4 &value);

    const std::string &GetName() const {
        return m_name;
    }

private:
    int FindUnifrom(const std::string &name);

    std::unordered_map<GLenum, std::string> Parse(const std::string &source);

    void Compile(const std::unordered_map<GLenum, std::string> &shaderSources);

private:
    uint32_t m_idx;
    std::string m_name;
};

class ShaderManager {
public:
    void Add(const std::string &name, Shader *shader);
    void Add(Shader *shader);
    
    Shader *Load(const std::string &path);
    Shader *Load(const std::string &name, const std::string &path);

    Shader *Get(const std::string &name);

    bool Exists(const std::string &name) const;

private:
    std::unordered_map<std::string, Shader *> m_Shaders;
};