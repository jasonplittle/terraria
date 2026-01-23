#pragma once

class VertexBuffer
{
public:
    VertexBuffer(const void* data, unsigned int size);
    VertexBuffer(const void* data, unsigned int size, bool dynamic);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
    void AddDynamicData(const void* data, unsigned int size);

private:
    unsigned int m_renderer_id;
    bool m_isDynamic = false;
};