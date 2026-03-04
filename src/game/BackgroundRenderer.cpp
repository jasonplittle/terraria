#include "BackgroundRenderer.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

BackgroundRenderer::BackgroundRenderer()
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

    m_shader = std::make_unique<Shader>("src/renderer/shaders/Background.shader");
    m_texture = std::make_unique<Texture>("resources/splash.png");

    m_vertexArray = std::make_unique<VertexArray>();
    m_indexBuffer = std::make_unique<IndexBuffer>(indicies, 6);
    m_vertexBuffer = std::make_unique<VertexBuffer>(verticies, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;

    layout.Push<float>(2);
    layout.Push<float>(2);
    m_vertexArray->AddBuffer(*m_vertexBuffer, layout);
}

void BackgroundRenderer::Render(Vec2 screenSize)
{
    Renderer renderer;


    float zoomX = screenSize.x;
    float zoomY = screenSize.y;

    glm::mat4 projection = glm::ortho(-zoomX, zoomX, -zoomY, zoomY, -1.0f, 1.0f);

    // glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(
        zoomX * 2,
        zoomY * 2,
        1.0f
    ));

    glm::mat4 mvp = projection * view * model;


    m_shader->Bind();
    m_shader->SetUniformMat4f("u_MVP", mvp);
    
    m_texture->Bind();
    m_shader->SetUniform1i("u_Texture", 0);
    renderer.Draw(*m_vertexArray, *m_indexBuffer, *m_shader);

}


