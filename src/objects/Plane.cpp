/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Plane
*/

#include "objects/Plane.hpp"

Plane::Plane(sf::Vector3f corner1, sf::Vector3f corner2, sf::Color color,
sf::Color emmsionColor, float intensity) :
Object(corner1, color, emmsionColor, intensity)
{
    _triangles[0] = Triangle(corner1, corner2, sf::Vector3f(corner1.x, corner1.y, corner2.z), color, emmsionColor, intensity);
    _triangles[1] = Triangle(corner1, sf::Vector3f(corner2.x, corner1.y, corner1.z), corner2, color, emmsionColor, intensity);
}

bool Plane::intersect(Ray *ray)
{
    return _triangles[0].intersect(ray) || _triangles[1].intersect(ray);
}

sf::Vector3f Plane::getIntersection(Ray *ray)
{
    if (_triangles[0].intersect(ray))
        return _triangles[0].getIntersection(ray);
    return _triangles[1].getIntersection(ray);
}

sf::Vector3f Plane::getNormal(sf::Vector3f inter)
{
    return _triangles[0].getNormal(inter);
}
