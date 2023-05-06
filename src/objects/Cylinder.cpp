/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Cylinder
*/

#include "objects/Cylinder.hpp"

Cylinder::Cylinder(Vec3 pos, Vec3 dir, float radius, float length,
sf::Color color, sf::Color emmsionColor, float intensity) :
AObject(pos, color, emmsionColor, intensity)
{
    _dir = Math::normalize(dir);
    _radius = radius;
    _length = length;
}

bool Cylinder::intersect(const Ray &ray, Vec3 &intersection) const
{
    Vec3 dist = ray.getOrigin() - _pos;
    float a = Math::dot(ray.getDir(), ray.getDir()) - powf(Math::dot(ray.getDir(), _dir), 2);
    float b = 2 * (Math::dot(ray.getDir(), dist) - Math::dot(ray.getDir(), _dir) * Math::dot(dist, _dir));
    float c = Math::dot(dist, dist) - powf(Math::dot(dist, _dir), 2) - powf(_radius, 2);
    float delta = powf(b, 2) - 4 * a * c;

    if (delta < 0)
        return false;
    float t1 = (-b - sqrtf(delta)) / (2 * a);
    float t2 = (-b + sqrtf(delta)) / (2 * a);
    if (_length == INF) {
        if (t1 < 0 && t2 < 0)
            return false;
        if (t1 < 0)
            intersection = ray.getOrigin() + ray.getDir() * t2;
        if (t2 < 0)
            intersection = ray.getOrigin() + ray.getDir() * t1;
        intersection = ray.getOrigin() + ray.getDir() * std::min(t1, t2);
        return true;
    }
    Vec3 inter1 = ray.getOrigin() + ray.getDir() * t1;
    Vec3 inter2 = ray.getOrigin() + ray.getDir() * t2;
    Vec3 dist1 = inter1 - _pos;
    Vec3 dist2 = inter2 - _pos;
    float proj1 = Math::dot(dist1, _dir);
    float proj2 = Math::dot(dist2, _dir);
    if ((proj1 < 0 || proj1 > _length ) && (proj2 < 0 || proj2 > _length))
        return false;
    if (proj1 < 0 || proj1 > _length)
        intersection = inter2;
    else
        intersection = inter1;
    return true;
}

Vec3 Cylinder::getNormal(const Vec3 &inter, unused const Ray &ray) const
{
    Vec3 dist = inter - _pos;
    Vec3 proj = Math::proj(dist, _dir);
    Vec3 normal = dist - proj;
    return Math::normalize(normal);
}

void Cylinder::setHeight(const float &height)
{
    if (height <= 0)
        throw InvalidParameterValueException("cylinder height must be positive");
    _length = height;
}

void Cylinder::setRadius(const float &radius)
{
    if (radius <= 0)
        throw InvalidParameterValueException("cylinder radius must be positive");
    _radius = radius;
}
