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

#include "World.hpp"

class WorldRenderer
{
public:
    WorldRenderer();
    void Render(const World& world);

private:
    std::unique_ptr<Texture> m_texture;
    std::unique_ptr<Shader> m_shader;
    
    std::unique_ptr<VertexArray> m_vertexArray;
    std::unique_ptr<IndexBuffer> m_indexBuffer;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;
};