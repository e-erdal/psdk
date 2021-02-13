#include "VertexArray.h"

VertexArray::VertexArray() {
#if CURRENT_API_OPENGL
    glCreateVertexArrays(1, &m_idx);
#endif
}

VertexArray::~VertexArray() {
#if CURRENT_API_OPENGL
    glDeleteVertexArrays(1, &m_idx);
#endif
}

void VertexArray::Bind() {
#if CURRENT_API_OPENGL
    glBindVertexArray(m_idx);
#endif
}
void VertexArray::Unbind() {
#if CURRENT_API_OPENGL
    glBindVertexArray(0);
#endif
}

void VertexArray::AddVertexBuffer(VertexBuffer *vertexBuffer) {
#if CURRENT_API_OPENGL
    if (!vertexBuffer->GetLayout().GetElements().size()) {
        DEBUG_LOG_ERROR("Vertex buffer size cannot be 0.");
        return;
    }

    glBindVertexArray(m_idx);
    vertexBuffer->Bind();

    const auto &layout = vertexBuffer->GetLayout();
    for (auto &&elem : layout) {
        switch (elem.type) {
            case ShaderDataType::Float:
            case ShaderDataType::Vec2:
            case ShaderDataType::Vec3:
            case ShaderDataType::Vec4: {
                glEnableVertexAttribArray(m_vboidx);
                glVertexAttribPointer(
                    m_vboidx, elem.GetComponentCount(), ShaderDataTypeToBaseType(elem.type), elem.normalized, layout.GetStride(), (const void *)elem.offset);
                m_vboidx++;
                break;
            }
            case ShaderDataType::Int:
            case ShaderDataType::IVec2:
            case ShaderDataType::IVec3:
            case ShaderDataType::IVec4:
            case ShaderDataType::Bool: {
                glEnableVertexAttribArray(m_vboidx);
                glVertexAttribIPointer(m_vboidx, elem.GetComponentCount(), ShaderDataTypeToBaseType(elem.type), layout.GetStride(), (const void *)elem.offset);
                m_vboidx++;
                break;
            }
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4: {
                uint8_t count = elem.GetComponentCount();
                for (uint8_t i = 0; i < count; i++) {
                    glEnableVertexAttribArray(m_vboidx);
                    glVertexAttribPointer(m_vboidx, elem.GetComponentCount(), ShaderDataTypeToBaseType(elem.type), elem.normalized, layout.GetStride(),
                        (const void *)(elem.offset + sizeof(float) * count * i));

                    glVertexAttribDivisor(m_vboidx, 1);
                    m_vboidx++;
                }
                break;
            }
            default: break;
        }
    }

    m_vertexBuffers.push_back(vertexBuffer);
#endif
}

void VertexArray::SetIndexBuffer(IndexBuffer *indexBuffer) {
#if CURRENT_API_OPENGL
    glBindVertexArray(m_idx);
    indexBuffer->Bind();

    m_indexBuffer = indexBuffer;
#endif
}