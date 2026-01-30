#include "WorldRenderer.hpp"


WorldRenderer::WorldRenderer()
{
    m_shader = std::make_unique<Shader>("src/renderer/shaders/Tile.shader");
    m_texture = std::make_unique<Texture>("resources/Tiles_1.png");

}



void WorldRenderer::Render(const World& world, const Player& player, Vec2 screenSize)
{
    Renderer renderer;

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0));


    float zoomX = screenSize.x * 0.5f / 2.0f;
    float zoomY = screenSize.y * 0.5f / 2.0f;
    
    glm::mat4 projection = glm::ortho(-zoomX, zoomX, -zoomY, zoomY, -1.0f, 1.0f);

    glm::vec2 cameraPos = 
    {
        player.GetPlayerPosition().x + player.GetPlayerSize().x * 0.5,
        player.GetPlayerPosition().y + player.GetPlayerSize().y * 0.5
    };

    // cameraPos.y = glm::clamp(
    //     cameraPos.y,
    //     HALF_H,
    //     worldHeight - HALF_H
    // );

    // model = glm::scale(model, glm::vec3(16.0f, 16.0f, 1.0f));

    
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraPos.x, -cameraPos.y, 0));
    
    
    glm::mat4 mvp = projection * view * model;

    m_shader->Bind();
    m_texture->Bind();
    m_shader->SetUniform1i("u_Atlas", 0);
    m_shader->SetUniformMat4f("u_MVP", mvp);

    renderer.Draw(world.GetChunk().GetVertexArray(), *m_shader);
}




