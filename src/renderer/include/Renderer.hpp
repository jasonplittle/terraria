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

    void Viewport(int width, int height) const;

    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    void Draw(const VertexArray& va, const Shader& shader);
};