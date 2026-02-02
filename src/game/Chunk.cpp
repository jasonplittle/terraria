#include "Chunk.hpp"

#include "FastNoiseLite.h"


Chunk::Chunk(int chunkX) : m_chunkX(chunkX)
{
    m_vertexArray = std::make_unique<VertexArray>();

    generateTileMap();
    generateTileMesh();
}

int GetSurfaceHeight(int worldX, const FastNoiseLite& noise)
{
    float n = noise.GetNoise((float)worldX, 0.0f); // -1 .. 1
    n = (n + 1.0f) * 0.5f;                          //  0 .. 1

    constexpr int BASE_HEIGHT = 64;
    constexpr int AMPLITUDE   = 20;

    return BASE_HEIGHT + int(n * AMPLITUDE);
}

void Chunk::generateTileMap()
{
    FastNoiseLite noise;
    // noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetSeed(1337);
    noise.SetFrequency(0.01f);

    FastNoiseLite caveNoise;
    caveNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    caveNoise.SetFrequency(0.05f);
    caveNoise.SetSeed(999);

    for (int x = 0; x < CHUNK_WIDTH; x++)
    {
        int worldX = m_chunkX * CHUNK_WIDTH + x;
        int surfaceY = GetSurfaceHeight(worldX, noise);

        for (int y = 0; y < CHUNK_HEIGHT; y++)
        {
            int worldY = y;

            float cave = caveNoise.GetNoise((float)worldX, (float)worldY);

            Tile tile;

            if (worldY > surfaceY)
                tile = Tile::AIR;
            else if (worldY == surfaceY)
                tile = Tile::DIRT;
                // tile = Tile::GRASS;
            else if (worldY >= surfaceY - 5)
                tile = Tile::DIRT;
            else if (worldY < surfaceY - 5 && cave > 0.4f)
                tile = Tile::AIR;
            else
                tile = Tile::STONE;

            m_tileMap[y * CHUNK_WIDTH + x] = tile;
        
            // float n = noise.GetNoise((float)x, (float)y);
            // n = (n + 1.0f) * 0.5f;

            // if (n < 0.3) m_tileMap[y * CHUNK_WIDTH + x] = Tile::STONE;
            // else if (n < 0.6) m_tileMap[y * CHUNK_WIDTH + x] = Tile::DIRT;
            // else m_tileMap[y * CHUNK_WIDTH + x] = Tile::AIR;
        }
    }
}

void Chunk::generateTileMesh()
{
    std::vector<Vertex> vertices;
    vertices.reserve(20000); // avoid reallocs

    float worldXOffset = m_chunkX * CHUNK_WIDTH * TILE_SIZE;

    for (int y = 0; y < CHUNK_HEIGHT; y++)
    {
        for (int x = 0; x < CHUNK_WIDTH; x++)
        {
            Tile tile = getTile(x, y);
            if (tile == AIR)
                continue;

            // skip fully surrounded tiles
            // if (GetTile(chunk, x - 1, y) != AIR &&
            //     GetTile(chunk, x + 1, y) != AIR &&
            //     GetTile(chunk, x, y - 1) != AIR &&
            //     GetTile(chunk, x, y + 1) != AIR)
            //     continue;

            // if (m_tileMap[(y * CHUNK_WIDTH) + x - 1] != AIR &&
            //     m_tileMap[(y * CHUNK_WIDTH) + x + 1] != AIR &&
            //     m_tileMap[((y - 1) * CHUNK_WIDTH) + x] != AIR &&
            //     m_tileMap[((y + 1) * CHUNK_WIDTH) + x] != AIR)
            //     continue;

            UVRect uv = GetTileUV(tile);

            float x0 = worldXOffset + x * TILE_SIZE;
            float y0 = y * TILE_SIZE;
            float x1 = x0 + TILE_SIZE;
            float y1 = y0 + TILE_SIZE;

            AddQuad(vertices, x0, y0, x1, y1, uv, tile);
        }
    }

    m_vertexBuffer = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(Vertex));

    VertexBufferLayout layout;

    layout.Push<float>(2);
    layout.Push<float>(2);
    layout.Push<float>(1);
    m_vertexArray->AddBuffer(*m_vertexBuffer, layout);
    m_vertexArray->SetVertexCount(vertices.size());
}


