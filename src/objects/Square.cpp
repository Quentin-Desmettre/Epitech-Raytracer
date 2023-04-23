/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Square
*/

#include "objects/Square.hpp"

Square::Square(Vec3 corner1, Vec3 corner2, sf::Color color, sf::Color emmsionColor, float intensity) :
AObject(corner1, color, emmsionColor, intensity)
{
    _triangles[0] = Triangle(corner1, corner2, Vec3(corner1.x, corner1.y, corner2.z), color, emmsionColor, intensity);
    _triangles[1] = Triangle(corner1, Vec3(corner2.x, corner1.y, corner1.z), corner2, color, emmsionColor, intensity);
    _triangles[2] = Triangle(corner1, Vec3(corner1.x, corner2.y, corner2.z), Vec3(corner2.x, corner1.y, corner1.z), color, emmsionColor, intensity);
    _triangles[3] = Triangle(Vec3(corner2.x, corner1.y, corner1.z), Vec3(corner1.x, corner2.y, corner2.z), corner2, color, emmsionColor, intensity);
}

bool Square::intersect(const Ray &ray) const
{
    return _triangles[0].intersect(ray) || _triangles[1].intersect(ray) ||
    _triangles[2].intersect(ray) || _triangles[3].intersect(ray);
}

Vec3 Square::getIntersection(const Ray &ray) const
{
    if (_triangles[0].intersect(ray))
        return _triangles[0].getIntersection(ray);
    return _triangles[1].getIntersection(ray);
}

Vec3 Square::getNormal(const Vec3 &inter, const Ray &ray) const
{
    return _triangles[0].getNormal(inter, ray);
}
