/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Sphere
*/

#include "objects/Sphere.hpp"

Sphere::Sphere(Vec3 pos, sf::Color color, float radius, sf::Color emmsionColor, float intensity) :
AObject(pos, color, emmsionColor, intensity), _radius(radius)
{
}

void Sphere::setTransparency(const bool &transparency)
{
    _transparency = transparency;
    _refractiveIndex = 1.5f;
}

float Sphere::getDelta(const Ray &ray) const
{
    Vec3 origin = ray.getOrigin();
    Vec3 dir = ray.getDir();
    float a = Math::dot(dir, dir);
    float b = 2 * Math::dot(dir, origin);
    float c = Math::dot(origin, origin) - _radius * _radius;

    return b * b - 4 * a * c;
}

float Sphere::getIntersections(const Ray &ray) const
{
    Vec3 origin = ray.getOrigin();
    Vec3 dir = ray.getDir();
    float a = Math::dot(dir, dir);
    float b = 2 * Math::dot(dir, origin);
    float c = Math::dot(origin, origin) - _radius * _radius;
    float delta = b * b - 4.0f * a * c;

    return (-b - sqrtf(delta)) / (2.0f * a);
}

bool Sphere::intersect(const Ray &ray, Vec3 &intersection) const
{
    Ray r = transformRay(ray);
    float t = getIntersections(r);

    if (t < 0 || t != t) // t != t is a check for NaN
        return false;
    // Get the intersection point, and put it back in the world space
    intersection = _transformationsMatrix * (r.getOrigin() + r.getDir() * t);
    return true;
}

Vec3 Sphere::getNormal(const Vec3 &inter, unused const Ray &ray) const
{
    return Math::normalize(inter - _pos);
}
