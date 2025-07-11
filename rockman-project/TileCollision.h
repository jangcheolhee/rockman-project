#pragma once

enum TileType
{
    EMPTY,
    BLOCK,
    LADDER
};

class TileCollision
{
public:
    bool loadFromFile(const std::string& filename);
    TileType getTileType(int x, int y) const;

protected:
    sf::Image collisionImage;
};
