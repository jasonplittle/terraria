#pragma once

#include "VertexBufferLayout.hpp"
#include "VertexBuffer.hpp"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void SetVertexCount(unsigned int count) { m_vertexCount = count; }
    unsigned int GetVertexCount() const { return m_vertexCount; }

    void Bind() const;
    void Unbind() const;

private:
    unsigned int m_renderer_id;

    unsigned int m_vertexCount = 0;

};