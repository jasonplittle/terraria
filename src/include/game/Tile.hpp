#pragma once


enum TileType
{
    AIR = 0,
    GRASS,
    DIRT,
    STONE
};

class Tile
{
public:
    Tile();
    Tile(TileType TileType);

    TileType GetTileType() const { return m_tileType; }

private:
    TileType m_tileType;
};