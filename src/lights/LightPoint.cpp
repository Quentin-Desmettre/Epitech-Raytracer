/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** LightPoint
*/

#include "lights/LightPoint.hpp"

LightPoint::LightPoint(Vec3 pos, sf::Color color, float intensity)
{
    _pos = pos;
    _color = color;
    _intensity = intensity;
}

LightPoint::~LightPoint()
{
}

Vec3 LightPoint::getPos() const
{
    return _pos;
}

sf::Color LightPoint::getColor() const
{
    return _color;
}

Vec3 LightPoint::getColorF() const
{
    Vec3 colorF;
    colorF.x = _color.r / 255.0f;
    colorF.y = _color.g / 255.0f;
    colorF.z = _color.b / 255.0f;
    return colorF;
}

float LightPoint::getIntensity() const
{
    return _intensity;
}

void LightPoint::setPos(Vec3 pos)
{
    pos = _pos;
}

void LightPoint::setColor(sf::Color color)
{
    color = _color;
}

