#include "WorldRenderer.hpp"


WorldRenderer::WorldRenderer()
{
    m_shader = std::make_unique<Shader>("src/renderer/shaders/Tile.shader");
    m_texture = std::make_unique<Texture>("resources/Tiles_1.png");

}



void WorldRenderer::Render(const World& world, Vec2 screenSize)
{
    Renderer renderer;

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0));
    // model = glm::scale(model, glm::vec3(16.0f, 16.0f, 1.0f));

    glm::mat4 projection = glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    
    
    glm::mat4 mvp = projection * view * model;

    m_shader->Bind();
    m_texture->Bind();
    m_shader->SetUniform1i("u_Atlas", 0);
    m_shader->SetUniformMat4f("u_MVP", mvp);

    renderer.Draw(world.GetChunk().GetVertexArray(), *m_shader);
}




