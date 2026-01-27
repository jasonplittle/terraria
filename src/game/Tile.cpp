#include "Tile.hpp"


Tile::Tile() : m_tileType(TileType::AIR) {}

Tile::Tile(TileType type) : m_tileType(type) {}