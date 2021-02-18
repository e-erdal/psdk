//
// Created on February 13th 2021 by loanselot1.
//
// Purpose: Main shader handler of SDK.
//

#pragma once

#include "pch.h"
#include <unordered_map>

enum class eShaderType : uint8_t { Fragment = 0, Vertex = 1 };

class ShaderManager {
public:
    void Add(const std::string &key, bgfx::RendererType::Enum renderer, eShaderType type, uint8_t *data, uint32_t dataLen);

    bgfx::ProgramHandle LoadProgram(const std::string &key);
    bgfx::ShaderHandle LoadShader(const std::string &key, const eShaderType shaderType);
    void InitializeSpriteShaders();

private:
    struct Shader {
        std::string name;
        bgfx::RendererType::Enum renderer;
        eShaderType type;

        uint8_t *code;
        uint32_t code_len;
    };

    std::unordered_map<std::string, bgfx::ProgramHandle> m_programs;

    std::vector<Shader> m_shaders;
};