#pragma once

#include "Chunk.hpp"

#include "UtilLib.hpp"

#include <map>



class World
{
public:
    World();

    const Chunk& GetChunk(float worldX) const;

    bool IsSolid(int x, int y) const;

private:
    std::map<int, Chunk> m_chunks;


};