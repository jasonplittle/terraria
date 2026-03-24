#include "World.hpp"

#include <cmath>
#include <iostream>


World::World()
{
    m_chunks.try_emplace(0, Chunk(0));
    m_chunks.try_emplace(1, Chunk(1));
    m_chunks.try_emplace(-1, Chunk(-1));
}


int World::GetSurfaceHeight(float worldX)
{
    return GetChunk(worldX).GetSurfaceHeight(worldX);
}

bool World::IsSolid(int worldTileX, int y)
{
    // std::cout << worldX << " " << y << std::endl;

    Tile tile = GetChunk(worldTileX * TILE_SIZE).getTileFromWorldTileX(worldTileX, y);
    return tile != AIR && tile != CAVE;
}

const Chunk& World::GetChunk(float worldX, int offset)
{
    int chunkCoord = (int)std::floor(worldX / TILE_SIZE / CHUNK_WIDTH) + offset;
    // std::cout << chunkCoord << std::endl;

    if (m_chunks.find(chunkCoord) == m_chunks.end())
    {
        // std::cout << "New chunk at: " << chunkCoord << std::endl;

        m_chunks.try_emplace(chunkCoord, Chunk(chunkCoord));
    }

    return m_chunks.at(chunkCoord);
}

void World::Update(const Player& player)
{
    if (!player.IsInAir() && player.IsMining())
    {
        int worldX = player.GetPlayerPosition().x;
        int worldY = player.GetPlayerPosition().y;

        int chunkCoord = (int)std::floor(worldX / TILE_SIZE / CHUNK_WIDTH);

        Tile replaceTile;

        Tile tile = m_chunks.at(chunkCoord).getTileFromWorldX(worldX, worldY);
        // std::cout << tile << std::endl;

        if (tile == Tile::DIRT)
        {
            m_chunks.at(chunkCoord).SetTileFrom(worldX, worldY, Tile::AIR);
        }
        else if (tile == Tile::STONE)
        {
            m_chunks.at(chunkCoord).SetTileFrom(worldX, worldY, Tile::CAVE);
        }
    }

    if (player.IsAttacking())
    {
        int worldX = player.GetPlayerPosition().x + (player.IsMovingRight() ? TILE_SIZE : -TILE_SIZE);
        int worldY = player.GetPlayerPosition().y + TILE_SIZE;

        int chunkCoord = (int)std::floor(worldX / TILE_SIZE / CHUNK_WIDTH);
        Tile tile = m_chunks.at(chunkCoord).getTileFromWorldX(worldX, worldY);
        
        Tile replaceTile;
        
        if (tile == Tile::DIRT)
        {
            m_chunks.at(chunkCoord).SetTileFrom(worldX, worldY, Tile::AIR);
        }
        else if (tile == Tile::STONE)
        {
            m_chunks.at(chunkCoord).SetTileFrom(worldX, worldY, Tile::CAVE);
        }
    }

}
