#pragma once

#include <memory>
#include <array>

#include "VertexBuffer.hpp"
#include "VertexArray.hpp"

constexpr int CHUNK_WIDTH  = 32;
constexpr int CHUNK_HEIGHT = 128; // tall world

constexpr float TILE_SIZE    = 16.0f;

constexpr float ATLAS_W = 288.0f;
constexpr float ATLAS_H = 277.0f;

constexpr float U = TILE_SIZE / ATLAS_W;
constexpr float V = 1.0f - (TILE_SIZE / ATLAS_H);


// constexpr float U1 = (1.0f / 288.0f) * 16.0f;
// constexpr float V = ((1.0f / 277.0f) * 16.0f);
// constexpr float V0 = 1.0f - (V * 6.0f);
// constexpr float V1 = V0 + V;

constexpr int Index(int x, int y)
{
    return x + y * CHUNK_WIDTH;
}

struct UVRect
{
    float u0, v0;
    float u1, v1;
};

struct Vertex
{
    float x, y;   // world position
    float u, v;   // atlas UV
};

enum Tile
{
    AIR = 0,
    GRASS,
    DIRT,
    STONE
};

class Chunk
{
public:
    Chunk();

    const VertexArray& GetVertexArray() const { return *m_vertexArray; }

    // const std::array<Tile, CHUNK_WIDTH * CHUNK_HEIGHT> GetTileMap() const { return m_tileMap; }

private:


    void generateTileMap();
    void generateTileMesh();

    inline UVRect GetTileUV(Tile tile)
    {
        switch (tile)
        {
            case STONE: return {0.0f, V, U, 1.0f};
            // case DIRT:  return {0.25f, 0.0f, 0.5f, 0.25f};
            // case STONE: return {0.5f, 0.0f, 0.75f, 0.25f};
            default:    return {0, 0, 0, 0};
        }
    }

    inline Tile getTile(int x, int y)
    {
        if (x < 0 || x >= CHUNK_WIDTH ||
            y < 0 || y >= CHUNK_HEIGHT)
            return AIR;

        return m_tileMap[y * CHUNK_WIDTH + x];
    }

    inline void AddQuad(std::vector<Vertex>& verts,
                    float x0, float y0,
                    float x1, float y1,
                    const UVRect& uv)
    {
        verts.push_back({x0, y0, uv.u0, uv.v1}); // Bottom left
        verts.push_back({x1, y0, uv.u1, uv.v1}); // Bottom right
        verts.push_back({x1, y1, uv.u1, uv.v0}); // Top right

        verts.push_back({x0, y0, uv.u0, uv.v1}); // Bottom left
        verts.push_back({x1, y1, uv.u1, uv.v0}); // Top right
        verts.push_back({x0, y1, uv.u0, uv.v0}); // Top left
    }

    int chunkX = 0; // chunk coordinate in world X

    std::array<Tile, CHUNK_WIDTH * CHUNK_HEIGHT> m_tileMap;

    std::unique_ptr<VertexArray> m_vertexArray;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;


};