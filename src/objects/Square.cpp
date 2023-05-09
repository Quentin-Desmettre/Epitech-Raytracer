/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Square
*/

#include "objects/Square.hpp"

Square::Square(Vec3 point1, Vec3 point2, Vec3 point3, Vec3 point4,
sf::Color color, sf::Color emmsionColor, float intensity) :
AObject(point1, color, emmsionColor, intensity)
{
    _triangles[0] = Triangle(point1, point2, point3, color, emmsionColor, intensity);
    _triangles[1] = Triangle(point1, point3, point4, color, emmsionColor, intensity);

    _triangles[2] = Triangle(point1, point4, point3, color, emmsionColor, intensity);
    _triangles[3] = Triangle(point1, point3, point2, color, emmsionColor, intensity);
}

void Square::setPosition(const Vec3 &position)
{
    _triangles[0].setPosition(position);
    _triangles[1].setPosition(position);
    _triangles[2].setPosition(position);
    _triangles[3].setPosition(position);

    _triangles[0].setPoint<0>(position);
    _triangles[1].setPoint<0>(position);
    _triangles[2].setPoint<0>(position);
    _triangles[3].setPoint<0>(position);
}

void Square::setPoint2(const Vec3 &point)
{
    _triangles[0].setPoint<1>(point);
    _triangles[3].setPoint<2>(point);
}

void Square::setPoint3(const Vec3 &point)
{
    _triangles[0].setPoint<2>(point);
    _triangles[1].setPoint<1>(point);
    _triangles[2].setPoint<2>(point);
    _triangles[3].setPoint<1>(point);
}

void Square::setPoint4(const Vec3 &point)
{
    _triangles[1].setPoint<2>(point);
    _triangles[2].setPoint<1>(point);
}

bool Square::intersect(const Ray &ray, Vec3 &intersection) const
{
    return _triangles[0].intersect(ray, intersection) || _triangles[1].intersect(ray, intersection) ||
    _triangles[2].intersect(ray, intersection) || _triangles[3].intersect(ray, intersection);
}

Vec3 Square::getNormal(const Vec3 &inter, const Ray &ray) const
{
    Vec3 tmp;
    if (_triangles[0].intersect(ray, tmp))
        return _triangles[0].getNormal(inter, ray);
    return _triangles[2].getNormal(inter, ray);
}
