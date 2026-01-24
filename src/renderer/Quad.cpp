#include "Quad.hpp"


Quad::Quad()
{
    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0,
    };


    m_vertexArray = std::make_unique<VertexArray>();
    m_indexBuffer = std::make_unique<IndexBuffer>(indicies, 6);
}