#include "Rectangle.hpp"


struct Vertex
{
    Vec2 Position;
    Vec4 Color;
};

Rectangle::Rectangle(float x, float y, float w, float h, Vec4 color)
    : m_x(x), m_y(y), m_w(w), m_h(h), m_color({color.x, color.y, color.z, color.w})
{
    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0,
    };

    m_shader = std::make_unique<Shader>("src/renderer/shaders/Basic.shader");
    m_vertexArray = std::make_unique<VertexArray>();
    m_indexBuffer = std::make_unique<IndexBuffer>(indicies, 6);
    m_vertexBuffer = std::make_unique<VertexBuffer>(nullptr, 4 * sizeof(Vertex), true);

    VertexBufferLayout layout;

    layout.Push<float>(2);
    layout.Push<float>(4);
    m_vertexArray->AddBuffer(*m_vertexBuffer, layout);
}

void Rectangle::UpdatePosition(float dx, float dy)
{
    m_x += dx;
    m_y += dy;
}

void Rectangle::Draw(glm::mat4 projection)
{
    Vertex verticies[] = {
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


