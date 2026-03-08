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

#include "Player.hpp"
#include "Mob.hpp"

class MobRenderer
{
public:
    MobRenderer();

    void Render(const Mob& mob, const Player& player, Vec2 screenSize);

private:
    std::unique_ptr<Shader> m_shader;

    std::unique_ptr<VertexArray> m_vertexArray;
    std::unique_ptr<IndexBuffer> m_indexBuffer;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;

};