#include "WorldRenderer.hpp"


WorldRenderer::WorldRenderer()
{
    m_shader = std::make_unique<Shader>("src/renderer/shaders/Tile.shader");
    m_textureStone = std::make_unique<Texture>("resources/Tiles_1.png");
    m_textureDirt = std::make_unique<Texture>("resources/Tiles_0.png");

}


void WorldRenderer::Render(const World& world, const Player& player, Vec2 screenSize)
{
    Renderer renderer;

    glm::vec2 cameraPos = 
    {
        player.GetPlayerPosition().x,
        player.GetPlayerPosition().y
    };

    float zoomX = screenSize.x * 0.5 * 0.75;
    float zoomY = screenSize.y * 0.5 * 0.75;

    glm::mat4 projection = glm::ortho(-zoomX, zoomX, -zoomY, zoomY, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraPos.x, -cameraPos.y, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.0));    
    
    glm::mat4 mvp = projection * view * model;

    m_shader->Bind();
    m_textureStone->Bind(0);
    m_textureDirt->Bind(1);
    int samplers[2] = {0, 1};
    m_shader->SetUniform1iv("u_Atlas", 2, samplers);
    m_shader->SetUniformMat4f("u_MVP", mvp);

    renderer.Draw(world.GetChunk(player.GetPlayerPosition().x).GetVertexArray(), *m_shader);
}




