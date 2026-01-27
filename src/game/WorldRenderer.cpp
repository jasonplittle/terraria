#include "WorldRenderer.hpp"


WorldRenderer::WorldRenderer()
{
    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0,
    };

    float verticies[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f
    };

    m_shader = std::make_unique<Shader>("src/renderer/shaders/Texture.shader");
    m_texture = std::make_unique<Texture>("resources/Tiles_1.png");


    m_vertexArray = std::make_unique<VertexArray>();
    m_indexBuffer = std::make_unique<IndexBuffer>(indicies, 6);
    m_vertexBuffer = std::make_unique<VertexBuffer>(verticies, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;

    layout.Push<float>(2);
    layout.Push<float>(2);
    m_vertexArray->AddBuffer(*m_vertexBuffer, layout);
}


void WorldRenderer::Render(const World& world)
{
    for (const auto& tile : world.GetTileMap())
    {

        // If tile is air/
        // Find uv
        // Generate one large vb?

    }

}

