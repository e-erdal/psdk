//
// Created on February 13th 2021 by loanselot1.
//
// Purpose: Index/Vertex object abstraction for cross APIs.
//

#pragma once

#include "pch.h"

#include "Buffer.h"

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void Bind();
    void Unbind();

    void AddVertexBuffer(VertexBuffer *vertexBuffer);
    void SetIndexBuffer(IndexBuffer *indexBuffer);

    const std::vector<VertexBuffer *> &GetVertexBuffers() const {
        return m_vertexBuffers;
    }
    const IndexBuffer *GetIndexBuffer() const {
        return m_indexBuffer;
    }

private:
    uint32_t m_idx;
    uint32_t m_vboidx = 0;
    std::vector<VertexBuffer *> m_vertexBuffers;
    IndexBuffer *m_indexBuffer;
};