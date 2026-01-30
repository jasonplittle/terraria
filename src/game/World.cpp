#include "World.hpp"

#include <cmath>
#include <iostream>


bool World::IsSolid(int x, int y) const
{
    int tileX = (int)std::floor(x / TILE_SIZE);
    int tileY = (int)std::floor(y / TILE_SIZE);

    Tile tile = GetChunk().getTile(tileX, tileY);

    std::cout << "(" << tileX << ", " << tileY << ") - " << "(" << x << ", " << y << ")" << " - " << (tile == Tile::AIR ? "Air" : "Solid") << std::endl;    

    return tile != AIR;
}
