#include "TorchManager.hpp"

#include <glm/glm.hpp>
#include <iostream>

void TorchManager::Update(float dt, const Player& player, bool isPlacingTorch)
{
    m_placementTimer += dt;

    if (isPlacingTorch && m_placementTimer > 1.f)
    {
        AddTorch(player.GetPlayerPosition());
        m_placementTimer = 0.f;
    }
}

void TorchManager::AddTorch(Vec2 pos)
{
    bool placementOK = true;
    for (auto& torch : m_torches)
    {
        float distance = glm::length(glm::vec2(torch.x, torch.y) - glm::vec2(torch.x, torch.y));
        if (distance > 5.0f)
        {
            placementOK = false;
            break;
        }
    }

    if (placementOK)
    {
        m_torches.push_back(pos);
        std::cout << "Torch place: " << pos.x << ", " << pos.y << std::endl;
    }
}
