/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Cone
*/

#include "objects/Cone.hpp"

Cone::Cone(Vec3 pos, Vec3 dir, float height, float slope,
sf::Color color, sf::Color emmsionColor, float intensity) :
AObject(pos, color, emmsionColor, intensity)
{
    _dir = dir;
    _height = height;
    _slope = slope;
}

bool Cone::intersect(const Ray &ray, Vec3 &intersection) const
{
    Ray r = transformRay(ray);
    Vec3 oc = r.getOrigin();
    float dirDot = Math::dot(r.getDir(), _dir);
    float a = Math::dot(r.getDir(), r.getDir()) - (1 + _slope * _slope) * dirDot * dirDot;
    float b = 2 * (Math::dot(r.getDir(), oc) - (1 + _slope * _slope) * dirDot * Math::dot(oc, _dir));
    float c = Math::dot(oc, oc) - (1 + _slope * _slope) * Math::dot(oc, _dir) * Math::dot(oc, _dir);
    float delta = b * b - 4 * a * c;
    if (delta < 0)
        return false;
    float t1 = (-b - sqrtf(delta)) / (2 * a);
    float t2 = (-b + sqrtf(delta)) / (2 * a);
    if (t1 < 0 && t2 < 0)
        return false;
    float t = t1 < t2 ? t1 : t2;
    Vec3 tmp = r.getOrigin() + r.getDir() * t;
    if (_height > 0 && tmp.y < _pos.y)
        return false;
    if (_height > 0 && tmp.y > _pos.y + _height)
        return false;
    intersection = _transformationsMatrix * tmp;
    return true;
}

Vec3 Cone::getNormal(const Vec3 &inter, unused const Ray &ray) const
{
    Vec3 dist = inter - _pos;
    float proj = Math::dot(dist, _dir);
    Vec3 normal = dist - _dir * proj;
    normal = Math::normalize(normal);
    return normal;
}

void Cone::setHeight(const float &height)
{
    _height = height;
}

void Cone::setSlope(const float &slope)
{
    if (_slope <= 0)
        throw InvalidParameterValueException("slope");
    _slope = slope;
}
