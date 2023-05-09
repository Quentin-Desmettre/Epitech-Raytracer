/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** PointArray
*/

#include "render/PointArray.hpp"

PointArray::PointArray(sf::Vector2u size):
    _size(size),
    _start(0, 0)
{
    _pixels = std::make_unique<sf::Uint8[]>(_size.x * _size.y * 3);
}

sf::Uint8 *PointArray::getPixels() const
{
    return _pixels.get();
}

std::size_t PointArray::getSize() const
{
    return _size.x * _size.y * 3;
}

sf::Vector2u PointArray::getSizeVector() const
{
    return _size;
}

void PointArray::setStartPoint(sf::Vector2u start)
{
    _start = start;
}

void PointArray::resize(sf::Vector2u size)
{
    _size = size;
    _pixels = std::make_unique<sf::Uint8 []>(_size.x * _size.y * 3);
}

void PointArray::setPixel(sf::Vector2u pos, const Vec3 &color)
{
    std::size_t pixelPos = (pos.x - _start.x) * _size.y + (pos.y - _start.y);

    _pixels[pixelPos * 3] = static_cast<sf::Uint8>(color.x);
    _pixels[pixelPos * 3 + 1] = static_cast<sf::Uint8>(color.y);
    _pixels[pixelPos * 3 + 2] = static_cast<sf::Uint8>(color.z);
}

void PointArray::setPixel(sf::Vector2u pos, sf::Color color)
{
    std::size_t pixelPos = (pos.x - _start.x) * _size.y + (pos.y - _start.y);

    _pixels[pixelPos * 3] = color.r;
    _pixels[pixelPos * 3 + 1] = color.g;
    _pixels[pixelPos * 3 + 2] = color.b;
}

sf::Color PointArray::getPixel(sf::Vector2u pos) const
{
    std::size_t pixelPos = (pos.x - _start.x) * _size.y + (pos.y - _start.y);

    return {_pixels[pixelPos * 3], _pixels[pixelPos * 3 + 1], _pixels[pixelPos * 3 + 2]};
}
