#include "Rectangle.hpp"


Rectangle::Rectangle(float x, float y, float w, float h)
    : m_x(x), m_y(y), m_w(w), m_h(h)
{}

void Rectangle::UpdatePosition(float dx, float dy)
{
    m_x += dx;
    m_y += dy;
}

struct ColorVertex
{
    Vec2 position;
    Vec4 color;
};

ColorRectangle::ColorRectangle(float x, float y, float w, float h, Vec4 color)
    : Rectangle(x, y, w, h), m_color({color.x, color.y, color.z, color.w})
{
    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0,
    };

    m_shader = std::make_unique<Shader>("src/renderer/shaders/Basic.shader");
    m_vertexArray = std::make_unique<VertexArray>();
    m_indexBuffer = std::make_unique<IndexBuffer>(indicies, 6);
    m_vertexBuffer = std::make_unique<VertexBuffer>(nullptr, 4 * sizeof(ColorVertex), true);

    VertexBufferLayout layout;

    layout.Push<float>(2);
    layout.Push<float>(4);
    m_vertexArray->AddBuffer(*m_vertexBuffer, layout);
}

void ColorRectangle::Draw(glm::mat4 projection)
{
    ColorVertex verticies[] = {
        {{m_x, m_y}, m_color},
        {{m_x + m_w, m_y}, m_color},
        {{m_x + m_w, m_y + m_h}, m_color},
        {{m_x, m_y + m_h}, m_color}
    };

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 mvp = projection * view * model;
    m_shader->Bind();
    m_shader->SetUniformMat4f("u_MVP", mvp);

    m_vertexBuffer->Bind();
    m_vertexBuffer->AddDynamicData(verticies, sizeof(verticies));

    Renderer renderer;
    renderer.Draw(*m_vertexArray, *m_indexBuffer, *m_shader);
}


struct TextureVertex
{
    Vec2 position;
    Vec2 textureCoords;
};

TextureRectangle::TextureRectangle(float x, float y, float w, float h, const std::string& texturePath)
    : Rectangle(x, y, w, h)
{
    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0,
    };

    m_shader = std::make_unique<Shader>("src/renderer/shaders/Texture.shader");
    m_vertexArray = std::make_unique<VertexArray>();
    m_indexBuffer = std::make_unique<IndexBuffer>(indicies, 6);
    m_vertexBuffer = std::make_unique<VertexBuffer>(nullptr, 4 * sizeof(TextureVertex), true);
    m_texture = std::make_unique<Texture>(texturePath);

    VertexBufferLayout layout;

    layout.Push<float>(2);
    layout.Push<float>(2);
    m_vertexArray->AddBuffer(*m_vertexBuffer, layout);

    m_shader->Bind();
    m_texture->Bind();
    m_shader->SetUniform1i("u_Texture", 0);
}



TextureRectangle::TextureRectangle(float x, float y, float w, float h, const Texture& texture, AtlasPosition atlasPosition)
    : Rectangle(x, y, w, h), m_atlasPosition(atlasPosition)
{
    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0,
    };

    m_shader = std::make_unique<Shader>("src/renderer/shaders/Texture.shader");
    m_vertexArray = std::make_unique<VertexArray>();
    m_indexBuffer = std::make_unique<IndexBuffer>(indicies, 6);
    m_vertexBuffer = std::make_unique<VertexBuffer>(nullptr, 4 * 4 * sizeof(float), true);

    VertexBufferLayout layout;

    layout.Push<float>(2);
    layout.Push<float>(2);
    m_vertexArray->AddBuffer(*m_vertexBuffer, layout);

    m_shader->Bind();
    texture.Bind();
    m_shader->SetUniform1i("u_Texture", 0);
}



void TextureRectangle::Draw(glm::mat4 projection)
{
    float verticies[] = {
        m_x, m_y, m_atlasPosition.bottomLeft.x, m_atlasPosition.bottomLeft.y,
        m_x + m_w, m_y, m_atlasPosition.bottomRight.x, m_atlasPosition.bottomRight.y,
        m_x + m_w, m_y + m_h, m_atlasPosition.topRight.x, m_atlasPosition.topRight.y,
        m_x, m_y + m_h, m_atlasPosition.topLeft.x, m_atlasPosition.topLeft.y
    };

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 mvp = projection * view * model;
    m_shader->Bind();
    m_shader->SetUniformMat4f("u_MVP", mvp);

    m_vertexBuffer->Bind();
    m_vertexBuffer->AddDynamicData(verticies, sizeof(verticies));

    Renderer renderer;
    renderer.Draw(*m_vertexArray, *m_indexBuffer, *m_shader);
}

