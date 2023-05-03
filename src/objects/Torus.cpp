/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Torus
*/

#include "objects/Torus.hpp"
#include "Exceptions.hpp"

void Torus::setRadius(const float &radius)
{
    if (radius <= 0)
        throw InvalidParameterValueException("radius must be positive");
    _radius = radius;
}

void Torus::setThickness(const float &thickness)
{
    if (thickness <= 0)
        throw InvalidParameterValueException("thickness must be positive");
    _thickness = thickness;
}
