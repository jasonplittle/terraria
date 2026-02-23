#pragma once

#include "Chunk.hpp"
#include "Player.hpp"

#include "UtilLib.hpp"

#include <map>

class Player; // Forward declaration

class World
{
public:
    World();

    const Chunk& GetChunk(float worldX, int offset = 0);
    bool IsSolid(int worldTileX, int y);
    void Update(const Player& player);

private:
    std::map<int, Chunk> m_chunks;

};