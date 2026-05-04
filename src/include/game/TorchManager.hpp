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

private:
    std::vector<Vec2> m_torches;

    float m_placementTimer = 0;


};
