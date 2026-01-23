#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

struct Vec4 { float x, y, z, w; };
struct Vec2 { float x, y; };

class Rectangle
{
public:
    Rectangle(float x, float y, float w, float h, Vec4 color);

    void UpdatePosition(float dx, float dy);
    void Draw(glm::mat4 projection);

private:
    float m_x;
    float m_y;
    float m_w;
    float m_h;
    Vec4 m_color;

    std::unique_ptr<VertexArray> m_vertexArray;
    std::unique_ptr<IndexBuffer> m_indexBuffer;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;
    std::unique_ptr<Shader> m_shader;
};