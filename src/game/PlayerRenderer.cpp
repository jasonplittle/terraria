#include "PlayerRenderer.hpp"


PlayerRenderer::PlayerRenderer()
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

    m_vertexArray = std::make_unique<VertexArray>();
    m_indexBuffer = std::make_unique<IndexBuffer>(indicies, 6);
    m_vertexBuffer = std::make_unique<VertexBuffer>(verticies, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;

    layout.Push<float>(2);
    layout.Push<float>(2);
    m_vertexArray->AddBuffer(*m_vertexBuffer, layout);
}


void PlayerRenderer::Render(const Player& player, Vec2 screenSize)
{
    Renderer renderer;

    Vec2 playerPostion = player.GetPlayerPosition();

    // glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(screenSize.x * 0.5f, screenSize.y * 0.5f, 0.0));
    // model = glm::scale(model, glm::vec3(64.0f, 64.0f, 0.0f));

    // glm::mat4 projection = glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1.0f, 1.0f);
    // glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));


    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(playerPostion.x, playerPostion.y, 0.0));
    model = glm::scale(model, glm::vec3(player.GetPlayerSize().x, player.GetPlayerSize().y, 0.0f));

    glm::mat4 projection = glm::ortho(0.0f, screenSize.x, 0.0f, screenSize.y, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    glm::mat4 mvp = projection * view * model;


    for (const auto& sprite : player.GetSprites())
    {
        Vec4 color = sprite->GetColor();
        Vec4 uv = sprite->GetAtlasCoords(!player.IsMovingRight());
        
        m_shader->Bind();
        m_shader->SetUniformMat4f("u_MVP", mvp);
        m_shader->SetUniform4f("u_Color", color.x, color.y, color.z, color.w);
        m_shader->SetUniform4f("u_UV", uv.x, uv.y, uv.z, uv.w);
        
        sprite->GetTexture().Bind();
        m_shader->SetUniform1i("u_Texture", 0);
        renderer.Draw(*m_vertexArray, *m_indexBuffer, *m_shader);
    }
}

