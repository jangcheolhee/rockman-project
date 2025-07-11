#include "stdafx.h"
#include "TileCollision.h"

bool TileCollision::loadFromFile(const std::string& filename)
{
    return collisionImage.loadFromFile(filename);
}

TileType TileCollision::getTileType(int x, int y) const
{
    if (x < 0 || y < 0 || x >= (int)collisionImage.getSize().x || y >= (int)collisionImage.getSize().y)
        return EMPTY;

    sf::Color pixel = collisionImage.getPixel(x, y);

    if (pixel == sf::Color::Yellow)
        return BLOCK;
    else if (pixel == sf::Color::Red)
        return LADDER;

    return EMPTY;
}