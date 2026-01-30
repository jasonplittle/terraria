#pragma once

#include "Chunk.hpp"

#include "UtilLib.hpp"



class World
{
public:
    World() = default;

    const Chunk& GetChunk() const { return chunk; }

    bool IsSolid(float x, float y) const;

private:
    Chunk chunk;


};