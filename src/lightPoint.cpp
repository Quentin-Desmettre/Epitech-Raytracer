/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** lightPoint
*/

#include "lightPoint.hpp"
#include <iostream>

lightPoint::lightPoint(sf::Vector3f pos, sf::Color color, float intensity)
{
    _pos = pos;
    _color = color;
    _intensity = intensity;
}

lightPoint::~lightPoint()
{
}

sf::Vector3f lightPoint::getPos()
{
    return _pos;
}

sf::Color lightPoint::getColor()
{
    return _color;
}

sf::Vector3f lightPoint::getColorF()
{
    sf::Vector3f colorF;
    colorF.x = _color.r / 255.0f;
    colorF.y = _color.g / 255.0f;
    colorF.z = _color.b / 255.0f;
    return colorF;
}

float lightPoint::getIntensity()
{
    return _intensity;
}

void lightPoint::setPos(sf::Vector3f pos)
{
    pos = _pos;
}

void lightPoint::setColor(sf::Color color)
{
    color = _color;
}

