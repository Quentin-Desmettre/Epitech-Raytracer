/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Sphere
*/

#include "objects/Sphere.hpp"

Sphere::Sphere(sf::Vector3f pos, sf::Color color, float radius, sf::Color emmsionColor, float intensity) :
Object(pos, color, emmsionColor, intensity), _radius(radius)
{
}

bool Sphere::intersect(Ray *ray)
{
    sf::Vector3f origin = ray->getOrigin();
    sf::Vector3f dir = ray->getDir();

    a = Math::dot(dir, dir);
    b = 2 * Math::dot(dir, origin - _pos);
    c = Math::dot(origin - _pos, origin - _pos) - _radius * _radius;
    _delta = b * b - 4.0f * a * c;
    _lastRay = ray;
    return _delta >= 0;
}

sf::Vector3f Sphere::getIntersection(Ray *ray)
{
    if (ray != _lastRay)
        intersect(ray);
    float t = (-b - sqrt(_delta)) / (2.0f * a);

    if (t < 0)
        return sf::Vector3f(0, 0, 0);
    return ray->getOrigin() + ray->getDir() * t;
}

sf::Vector3f Sphere::getNormal(sf::Vector3f inter)
{
    return Math::normalize(inter - _pos);
}
