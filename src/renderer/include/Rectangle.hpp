#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "UtilLib.hpp"


class Rectangle
{
public:
    Rectangle(float x, float y, float w, float h);
    virtual ~Rectangle() = default;

    void UpdatePosition(float dx, float dy);
    virtual void Draw(glm::mat4 projection) = 0;

protected:
    float m_x;
    float m_y;
    float m_w;
    float m_h;

    std::unique_ptr<VertexArray> m_vertexArray;
    std::unique_ptr<IndexBuffer> m_indexBuffer;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;
    std::unique_ptr<Shader> m_shader;
};

class ColorRectangle : public Rectangle
{
public:
    ColorRectangle(float x, float y, float w, float h, Vec4 color);

    virtual void Draw(glm::mat4 projection) override;

private:
    Vec4 m_color;
};

class TextureRectangle : public Rectangle
{
public:
    TextureRectangle(float x, float y, float w, float h, const std::string& texturePath);
    TextureRectangle(float x, float y, float w, float h, const Texture& texture, AtlasPosition atlasPosition);

    virtual void Draw(glm::mat4 projection) override;

private:
    std::unique_ptr<Texture> m_texture;
    AtlasPosition m_atlasPosition = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
};