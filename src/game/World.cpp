#include "World.hpp"

#include "FastNoiseLite.h"


World::World()
{
    GenerateChunk();
}

void World::GenerateChunk()
{
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.02f);

    for (int y = 0; y < CHUNK_HEIGHT; y++)
    {
        for (int x = 0; x < CHUNK_WIDTH; x++)
        {
            float n = noise.GetNoise((float)x, (float)y);
            n = (n + 1.0f) * 0.5f;

            TileType tileType;

            if (n < 0.5) tileType = TileType::STONE;
            else tileType = TileType::AIR;

            
            m_tileMap[y * CHUNK_WIDTH + x] = Tile(tileType);
        }
    }

}