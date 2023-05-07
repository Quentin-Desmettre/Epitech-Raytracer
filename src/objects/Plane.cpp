/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Plane
*/

#include "objects/Plane.hpp"

Plane::Plane(Vec3 pos, Vec3 dir, sf::Color color, sf::Color emmsionColor, float intensity) :
AObject(pos, color, emmsionColor, intensity)
{
    _dir = dir;
}

void Plane::setAxis(const std::string &axis) {
    if (axis == "x")
        _dir = Vec3(1, 0, 0);
    else if (axis == "-x")
        _dir = Vec3(-1, 0, 0);
    else if (axis == "y")
        _dir = Vec3(0, 1, 0);
    else if (axis == "-y")
        _dir = Vec3(0, -1, 0);
    else if (axis == "z")
        _dir = Vec3(0, 0, 1);
    else if (axis == "-z")
        _dir = Vec3(0, 0, -1);
    else
        throw InvalidParameterValueException("axis");
}

void Plane::setPosition(const float &position) {
    _pos = _dir * position;
}

void Plane::computeTransformations()
{
    AObject::computeTransformations();
}

bool Plane::intersect(const Ray &ray, Vec3 &intersection) const
{
    Ray r = transformRay(ray);
    float dot = Math::dot(r.getDir(), _dir);
    float t = Math::dot(-r.getOrigin(), _dir) / (dot != 0 ? dot : 1);
    intersection = r.getOrigin() + r.getDir() * t;
    intersection = _transformationsMatrix * intersection;
    return dot != 0;
}

Vec3 Plane::getNormal(unused const Vec3 &inter, unused const Ray &ray) const
{
    return Math::normalize(_dir);
}
