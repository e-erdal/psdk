//
// Created on February 13th 2021 by loanselot1.
//
// Purpose: Helper utilities for buffers.
//

#pragma once

#include "pch.h"

enum class ShaderDataType {
    None = 0,
    Float,
    Vec2,
    Vec3,
    Vec4,
    Mat3,
    Mat4,
    Int,
    IVec2,
    IVec3,
    IVec4,
    Bool,
};

static uint32_t ShaderDataTypeSize(ShaderDataType type) {
    switch (type) {
        case ShaderDataType::Float: return 4;
        case ShaderDataType::Vec2: return 4 * 2;
        case ShaderDataType::Vec3: return 4 * 3;
        case ShaderDataType::Vec4: return 4 * 4;
        case ShaderDataType::Mat3: return 4 * 3 * 3;
        case ShaderDataType::Mat4: return 4 * 4 * 4;
        case ShaderDataType::Int: return 4;
        case ShaderDataType::IVec2: return 4 * 2;
        case ShaderDataType::IVec3: return 4 * 3;
        case ShaderDataType::IVec4: return 4 * 4;
        case ShaderDataType::Bool: return 1;
    }

    return 0;
}

#if CURRENT_API_OPENGL
static uint32_t ShaderDataTypeToBaseType(ShaderDataType type) {
    switch (type) {
        case ShaderDataType::Float: return GL_FLOAT;
        case ShaderDataType::Vec2: return GL_FLOAT;
        case ShaderDataType::Vec3: return GL_FLOAT;
        case ShaderDataType::Vec4: return GL_FLOAT;
        case ShaderDataType::Mat3: return GL_FLOAT;
        case ShaderDataType::Mat4: return GL_FLOAT;
        case ShaderDataType::Int: return GL_INT;
        case ShaderDataType::IVec2: return GL_INT;
        case ShaderDataType::IVec3: return GL_INT;
        case ShaderDataType::IVec4: return GL_INT;
        case ShaderDataType::Bool: return GL_BOOL;
    }

    return 0;
}
#else

// TODO
static uint32_t ShaderDataTypeToBaseType(ShaderDataType type) {
    return 0;
}
#endif