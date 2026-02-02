#pragma once

#include "Chunk.hpp"

#include "UtilLib.hpp"

#include <map>



class World
{
public:
    World();

    const Chunk& GetChunk(float worldX, int offset = 0);

    bool IsSolid(int x, int y);

private:
    std::map<int, Chunk> m_chunks;


};