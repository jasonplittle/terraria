#pragma once

#include <vector>
#include <GL/glew.h>

#include "ErrorUtils.hpp"

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned int normalised;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout
{
public:
    VertexBufferLayout() : m_stride(0) {};

    template<typename T>
    void Push(unsigned int count);

    inline const std::vector<VertexBufferElement>& GetElements() const { return m_elements; }
    inline const unsigned int GetStride() const { return m_stride; }

private:
    std::vector<VertexBufferElement> m_elements;
    unsigned int m_stride;
};