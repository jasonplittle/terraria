#pragma once

#include "ErrorUtils.hpp"

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"


class Renderer
{
public:
    void EnableBlending() const;
    void Clear() const;

    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
};