#include "World.hpp"

#include <cmath>
#include <iostream>


World::World()
{
    m_chunks.try_emplace(0, Chunk(0));
    m_chunks.try_emplace(1, Chunk(1));
    m_chunks.try_emplace(-1, Chunk(-1));
}


bool World::IsSolid(int x, int y)
{
    Tile tile = GetChunk(x).getTile(x, y);
    return tile != AIR;
}

const Chunk& World::GetChunk(float worldX, int offset)
{
    int chunkCoord = (int)std::floor(worldX / TILE_SIZE / CHUNK_WIDTH) + offset;

    if (m_chunks.find(chunkCoord) == m_chunks.end())
    {
        std::cout << "New chunk at: " << chunkCoord << std::endl;

        m_chunks.try_emplace(chunkCoord, Chunk(chunkCoord));
    }

    return m_chunks.at(chunkCoord);
}

