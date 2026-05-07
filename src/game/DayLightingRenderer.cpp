#include "DayLightingRenderer.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


DayLightingRenderer::DayLightingRenderer()
{
    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0,
    };

    float verticies[] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f,
        -1.0f,  1.0f
    };

    m_shader = std::make_unique<Shader>("src/renderer/shaders/DayLighting.shader");

    m_vertexArray = std::make_unique<VertexArray>();
    m_indexBuffer = std::make_unique<IndexBuffer>(indicies, 6);
    m_vertexBuffer = std::make_unique<VertexBuffer>(verticies, 4 * 2 * sizeof(float));

    VertexBufferLayout layout;

    layout.Push<float>(2);
    m_vertexArray->AddBuffer(*m_vertexBuffer, layout);
}

void DayLightingRenderer::Render(const DayLighting& dayLighting, const TorchManager& torchManager, const Player& player, Vec2 screenSize)
{
    Renderer renderer;

    float zoomX = screenSize.x * 0.5 * 0.75;
    float zoomY = screenSize.y * 0.5 * 0.75;

    glm::vec2 cameraPos = 
    {
        player.GetPlayerPosition().x,
        player.GetPlayerPosition().y
    };

    m_shader->Bind();
    m_shader->SetUniform1f("u_Lighting", dayLighting.GetLighting());
    m_shader->SetUniform2f("u_CameraPos", cameraPos.x, cameraPos.y);
    m_shader->SetUniform2f("u_HalfWorldSize", zoomX, zoomY);
    m_shader->SetUniform1f("u_TorchRadius", 100.0f);
    m_shader->SetUniform2fv("u_TorchPositions", torchManager.GetTorches().size(), &torchManager.GetTorches()[0].x);
    m_shader->SetUniform1i("u_TorchCount", torchManager.GetTorches().size());

    renderer.Draw(*m_vertexArray, *m_indexBuffer, *m_shader);
}