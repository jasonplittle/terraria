#pragma once

#include "VertexBufferLayout.hpp"
#include "VertexBuffer.hpp"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void Bind() const;
    void Unbind() const;

private:
    unsigned int m_renderer_id;

};