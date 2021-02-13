//
// Created on February 13th 2021 by loanselot1.
//
// Purpose: Hazel's buffer system.
//

#pragma once

#include "pch.h"

#include "Helpers.h"

struct BufferElement {
    std::string name;
    ShaderDataType type;
    uint32_t size;
    size_t offset;
    bool normalized;

    BufferElement() = default;

    // fucking retard
    // clang-format off
    BufferElement(ShaderDataType type, const std::string &name, bool normalized = false)
        : name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized) {}
    // clang-format on

    uint32_t GetComponentCount() const {
        switch (type) {
            case ShaderDataType::Float: return 1;
            case ShaderDataType::Vec2: return 2;
            case ShaderDataType::Vec3: return 3;
            case ShaderDataType::Vec4: return 4;
            case ShaderDataType::Mat3: return 3;
            case ShaderDataType::Mat4: return 4;
            case ShaderDataType::Int: return 1;
            case ShaderDataType::IVec2: return 2;
            case ShaderDataType::IVec3: return 3;
            case ShaderDataType::IVec4: return 4;
            case ShaderDataType::Bool: return 1;
        }

        return 0;
    }
};

class BufferLayout {
public:
    BufferLayout() {
    }

    BufferLayout(std::initializer_list<BufferElement> elements) : m_elements(elements) {
        CalculateOffsetsAndStride();
    }

    uint32_t GetStride() const {
        return m_stride;
    }
    const std::vector<BufferElement> &GetElements() const {
        return m_elements;
    }

    std::vector<BufferElement>::iterator begin() {
        return m_elements.begin();
    }
    std::vector<BufferElement>::iterator end() {
        return m_elements.end();
    }
    std::vector<BufferElement>::const_iterator begin() const {
        return m_elements.begin();
    }
    std::vector<BufferElement>::const_iterator end() const {
        return m_elements.end();
    }

private:
    void CalculateOffsetsAndStride() {
        size_t offset = 0;
        m_stride = 0;
        for (auto &element : m_elements) {
            element.offset = offset;
            offset += element.size;
            m_stride += element.size;
        }
    }

private:
    std::vector<BufferElement> m_elements;
    uint32_t m_stride = 0;
};

class VertexBuffer {
public:
    VertexBuffer(uint32_t size);
    VertexBuffer(float *vertices, uint32_t size);
    ~VertexBuffer();

    void Bind();
    void Unbind();

    void SetData(const void *data, uint32_t size);

    const BufferLayout &GetLayout() const {
        return m_layout;
    }

    void SetLayout(const BufferLayout &layout) {
        m_layout = layout;
    }

private:
    uint32_t m_idx;
    BufferLayout m_layout;
};

class IndexBuffer {
public:
    IndexBuffer(uint32_t *indices, uint32_t count);
    ~IndexBuffer();

    void Bind();
    void Unbind();

    uint32_t GetCount() const {
        return m_count;
    }

private:
    uint32_t m_idx;
    uint32_t m_count;
};