#pragma once

#include <memory>

#include "UtilLib.hpp"
#include "Player.hpp"

class TorchManager
{
public:
    TorchManager() = default;
    void Update(float dt, const Player& player, bool isPlacingTorch);
    void AddTorch(Vec2 pos);
    const std::vector<Vec2>& GetTorches() const { return m_torches; }

private:
    std::vector<Vec2> m_torches = {Vec2{0, 0}};

    float m_placementTimer = 0;
};
