#pragma once

#include "Chunk.hpp"

#include "UtilLib.hpp"



class World
{
public:
    World() = default;

    const Chunk& GetChunk() const { return chunk; }

    bool IsSolid(int x, int y) const;

private:
    Chunk chunk;


};