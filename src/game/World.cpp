#include "World.hpp"

#include <cmath>
#include <iostream>


World::World()
{
    m_chunks.try_emplace(0, Chunk());
}


bool World::IsSolid(int x, int y) const
{
    Tile tile = GetChunk(x).getTile(x, y);
    return tile != AIR;
}

const Chunk& World::GetChunk(float worldX) const
{
    int chunkCoord = (int)std::floor(worldX / TILE_SIZE / CHUNK_WIDTH);

    // std::cout << worldX << " " << chunkCoord << std::endl;

    return m_chunks.at(chunkCoord);
}
