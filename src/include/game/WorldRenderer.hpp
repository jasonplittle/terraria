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
#include "Player.hpp"

class WorldRenderer
{
public:
    WorldRenderer();
    void Render(World& world, const Player& player, Vec2 screenSize);

private:
    std::unique_ptr<Texture> m_textureStone;
    std::unique_ptr<Texture> m_textureDirt;
    std::unique_ptr<Shader> m_shader;

    bool m_worldNeedsRendering = true;
    
};