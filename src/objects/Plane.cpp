/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Plane
*/

#include "objects/Plane.hpp"

Plane::Plane(Vec3 corner1, Vec3 corner2, sf::Color color,
sf::Color emmsionColor, float intensity) :
Object(corner1, color, emmsionColor, intensity)
{
    _triangles[0] = Triangle(corner1, corner2, Vec3(corner1.x, corner1.y, corner2.z), color, emmsionColor, intensity);
    _triangles[1] = Triangle(corner1, Vec3(corner2.x, corner1.y, corner1.z), corner2, color, emmsionColor, intensity);
}

bool Plane::intersect(const Ray *ray) const
{
    return _triangles[0].intersect(ray) || _triangles[1].intersect(ray);
}

Vec3 Plane::getIntersection(const Ray *ray) const
{
    if (_triangles[0].intersect(ray))
        return _triangles[0].getIntersection(ray);
    return _triangles[1].getIntersection(ray);
}

Vec3 Plane::getNormal(Vec3 inter) const
{
    return _triangles[0].getNormal(inter);
}
