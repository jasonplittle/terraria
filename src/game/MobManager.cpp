#include "MobManager.hpp"

#include <random>


void MobManager::Update(float dt, Player& player, World& world)
{
    for (auto it = mobs.begin(); it != mobs.end(); )
    {
        it->Update(dt, player, world);
        bool isAlive = it->IsAlive();

        if (!isAlive)
            it = mobs.erase(it);
        else
            ++it;
    }


    m_spawnTimer += dt;

    if (m_spawnTimer < 3.0f)
        return;

    m_spawnTimer = 0.0;

    if (mobs.size() >= 20)
        return;

    
    static std::mt19937 gen(std::random_device{}());

    int screenLeft = player.GetPlayerPosition().x - 640.f;
    int screenRight = player.GetPlayerPosition().x + 640.f;
    int chunkEdgeLeft = player.GetPlayerPosition().x - (5 * CHUNK_WIDTH * TILE_SIZE);
    int chunkEdgeRight = player.GetPlayerPosition().x + (5 * CHUNK_WIDTH * TILE_SIZE);

    std::uniform_int_distribution<> dist1(chunkEdgeLeft, screenLeft);
    std::uniform_int_distribution<> dist2(screenRight, chunkEdgeRight);
    std::uniform_int_distribution<> pick(0, 1);

    int worldX = pick(gen) == 0 ? dist1(gen) : dist2(gen);

    // std::uniform_int_distribution<> dist1(screenLeft, screenRight);
    // int worldX = dist1(gen);

    int worldY = world.GetSurfaceHeight(worldX);

    spawn(worldX, worldY);
}

void MobManager::spawn(int worldX, int worldY)
{
    std::cout << "Spawn: " << worldX << ", " << worldY << std::endl;

    mobs.push_back(Mob(worldX, worldY));
}

