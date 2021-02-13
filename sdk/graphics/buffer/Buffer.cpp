#include "Buffer.h"

// Vertex buffer ////////////////////////////////////////////

VertexBuffer::VertexBuffer(uint32_t size) {
    glCreateBuffers(1, &m_idx);
    glBindBuffer(GL_ARRAY_BUFFER, m_idx);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(float *vertices, uint32_t size) {
    glCreateBuffers(1, &m_idx);
    glBindBuffer(GL_ARRAY_BUFFER, m_idx);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_idx);
}

void VertexBuffer::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, m_idx);
}

void VertexBuffer::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void *data, uint32_t size) {
    glBindBuffer(GL_ARRAY_BUFFER, m_idx);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

// Index buffer /////////////////////////////////////////////

IndexBuffer::IndexBuffer(uint32_t *indices, uint32_t count) : m_count(count) {

    glCreateBuffers(1, &m_idx);

    // GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
    // Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state.
    glBindBuffer(GL_ARRAY_BUFFER, m_idx);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {

    glDeleteBuffers(1, &m_idx);
}

void IndexBuffer::Bind() {

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idx);
}

void IndexBuffer::Unbind() {

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}