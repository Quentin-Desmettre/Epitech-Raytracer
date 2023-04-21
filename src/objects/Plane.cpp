/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Plane
*/

#include "objects/Plane.hpp"

Plane::Plane(Vec3 pos, Vec3 dir, sf::Color color, sf::Color emmsionColor, float intensity) :
Object(pos, color, emmsionColor, intensity)
{
    _dir = dir;
}

bool Plane::intersect(const Ray *ray) const
{
    float dot = Math::dot(ray->getDir(), _dir);
    return dot != 0;
}

Vec3 Plane::getIntersection(const Ray *ray) const
{
    float dot = Math::dot(ray->getDir(), _dir);
    float t = Math::dot(_pos - ray->getOrigin(), _dir) / dot;
    return ray->getOrigin() + ray->getDir() * t;
}

Vec3 Plane::getNormal(unused const Vec3 &inter, unused const Ray &ray) const
{
    return Math::normalize(_dir);
}
