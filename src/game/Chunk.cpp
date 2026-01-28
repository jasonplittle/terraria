#include "Chunk.hpp"

#include "FastNoiseLite.h"




Chunk::Chunk()
{

    m_vertexArray = std::make_unique<VertexArray>();

    generateTileMap();
    generateTileMesh();
}


void Chunk::generateTileMap()
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

            if (n < 0.5) m_tileMap[y * CHUNK_WIDTH + x] = Tile::STONE;
            else m_tileMap[y * CHUNK_WIDTH + x] = Tile::AIR;
        }
    }
}

void Chunk::generateTileMesh()
{
    std::vector<Vertex> vertices;
    vertices.reserve(20000); // avoid reallocs

    float worldXOffset = chunkX * CHUNK_WIDTH * TILE_SIZE;

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

            UVRect uv = GetTileUV(tile);

            float x0 = worldXOffset + x * TILE_SIZE;
            float y0 = y * TILE_SIZE;
            float x1 = x0 + TILE_SIZE;
            float y1 = y0 + TILE_SIZE;

            AddQuad(vertices, x0, y0, x1, y1, uv);
        }
    }

    m_vertexBuffer = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(Vertex));

    VertexBufferLayout layout;

    layout.Push<float>(2);
    layout.Push<float>(2);
    // layout.Push<float>(1); // texture index
    m_vertexArray->AddBuffer(*m_vertexBuffer, layout);
    m_vertexArray->SetVertexCount(vertices.size());
}


