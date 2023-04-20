/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** LightPoint
*/

#include "LightPoint.hpp"
#include <iostream>

LightPoint::LightPoint(sf::Vector3f pos, sf::Color color, float intensity)
{
    _pos = pos;
    _color = color;
    _intensity = intensity;
}

LightPoint::~LightPoint()
{
}

sf::Vector3f LightPoint::getPos()
{
    return _pos;
}

sf::Color LightPoint::getColor()
{
    return _color;
}

sf::Vector3f LightPoint::getColorF()
{
    sf::Vector3f colorF;
    colorF.x = _color.r / 255.0f;
    colorF.y = _color.g / 255.0f;
    colorF.z = _color.b / 255.0f;
    return colorF;
}

float LightPoint::getIntensity()
{
    return _intensity;
}

void LightPoint::setPos(sf::Vector3f pos)
{
    pos = _pos;
}

void LightPoint::setColor(sf::Color color)
{
    color = _color;
}

