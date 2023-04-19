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

float Sphere::getDelta(const Ray *ray) const
{
    sf::Vector3f origin = ray->getOrigin();
    sf::Vector3f dir = ray->getDir();
    float a = Math::dot(dir, dir);
    float b = 2 * Math::dot(dir, origin - _pos);
    float c = Math::dot(origin - _pos, origin - _pos) - _radius * _radius;

    return b * b - 4.0f * a * c;
}

float Sphere::getIntersections(const Ray *ray) const
{
    sf::Vector3f origin = ray->getOrigin();
    sf::Vector3f dir = ray->getDir();
    float a = Math::dot(dir, dir);
    float b = 2 * Math::dot(dir, origin - _pos);
    float c = Math::dot(origin - _pos, origin - _pos) - _radius * _radius;
    float delta = b * b - 4.0f * a * c;

    return (-b - sqrt(delta)) / (2.0f * a);
}

bool Sphere::intersect(const Ray *ray) const
{
    return getDelta(ray) >= 0;
}

sf::Vector3f Sphere::getIntersection(const Ray *ray) const
{
    float t = getIntersections(ray);

    if (t < 0 || t != t) // t != t is a check for NaN
        return sf::Vector3f(0, 0, 0);
    return ray->getOrigin() + ray->getDir() * t;
}

sf::Vector3f Sphere::getNormal(sf::Vector3f inter) const
{
    return Math::normalize(inter - _pos);
}
