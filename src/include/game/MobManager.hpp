#pragma once

#include "Mob.hpp"
#include "World.hpp"
#include "Player.hpp"

class MobManager
{
public:
    void Update(float dt, const Player& player, World& world);
    const std::vector<Mob>& GetMobs() const { return mobs; };

private:
    void spawn(int worldX, int worldY);
    std::vector<Mob> mobs;
    float m_spawnTimer = 0.0;

};
