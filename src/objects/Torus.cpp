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

bool Torus::intersect(const Ray &ray, Vec3 &intersection) const
{
    // Formula of a torus:
    // (x^2 + y^2 + z^2 + R^2 - r^2)^2 - 4R^2(x^2 + y^2) = 0
    // Parametric equation of a line:
    // x = x0 + t * dx
    // y = y0 + t * dy
    // z = z0 + t * dz

    // So, intersection between a line and a torus is:
    // (x0 + t * dx)^2 + (y0 + t * dy)^2 + (z0 + t * dz)^2 + R^2 - r^2)^2 - 4R^2((x0 + t * dx)^2 + (y0 + t * dy)^2) = 0

}
