#pragma once

#include <array>

#include "UtilLib.hpp"

#include "Tile.hpp"


constexpr int CHUNK_WIDTH  = 32;
constexpr int CHUNK_HEIGHT = 32; // tall world


// class Chunk
// {
// public:
//     Chunk(std::array<Tile, CHUNK_WIDTH * CHUNK_HEIGHT> ) : ;

// private:
//     std::array<Tile, CHUNK_WIDTH * CHUNK_HEIGHT> m_tileMap;
// };

class World
{
public:
    World();

    void GenerateChunk();

    const std::array<Tile, CHUNK_WIDTH * CHUNK_HEIGHT> GetTileMap() const { return m_tileMap; }

private:
    IVec2 currentChunkIndex = { 0, 0 };

    // std::vector<Chunk> chunks

    std::array<Tile, CHUNK_WIDTH * CHUNK_HEIGHT> m_tileMap;




    // current chunk



};