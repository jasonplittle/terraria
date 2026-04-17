#pragma once

#include <memory>

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "UtilLib.hpp"
#include "Renderer.hpp"

#include "DayLighting.hpp"


class DayLightingRenderer
{
public:
    DayLightingRenderer();

    void Render(const DayLighting& dayLighting, Vec2 screenSize);

private:
    std::unique_ptr<Shader> m_shader;

    std::unique_ptr<VertexArray> m_vertexArray;
    std::unique_ptr<IndexBuffer> m_indexBuffer;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;
};