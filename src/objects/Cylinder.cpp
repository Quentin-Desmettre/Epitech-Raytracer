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
    Ray r = transformRay(ray);
    Vec3 dir = r.getDir();
    Vec3 pos = r.getOrigin();
    float a = POW2(dir.x) + POW2(dir.z);
    float b = 2 * (dir.x * pos.x + dir.z * pos.z);
    float c = POW2(pos.x) + POW2(pos.z) - POW2(_radius);
    float delta = POW2(b) - 4 * a * c;

    if (delta < 0)
        return false;
    float t1 = (-b - sqrtf(delta)) / (2 * a);
    float t2 = (-b + sqrtf(delta)) / (2 * a);
    if (_length == INF) {
        if (t1 < 0 && t2 < 0)
            return false;
        intersection = r.getOrigin() + r.getDir() * std::min(t1, t2);
        intersection = transformPosInverse(intersection);
        return true;
    }
    Vec3 inter1 = r.getOrigin() + r.getDir() * t1;
    Vec3 inter2 = r.getOrigin() + r.getDir() * t2;
    if ((inter1.y < 0 || inter1.y > _length ) && (inter2.y < 0 || inter2.y > _length))
        return false;
    if (inter1.y < 0 || inter1.y > _length)
        intersection = inter2;
    else
        intersection = inter1;
    intersection = transformPosInverse(intersection);
    return true;
}

Vec3 Cylinder::getNormal(const Vec3 &inter, unused const Ray &ray) const
{
    Vec3 localInter = transformPos(inter);
    return Math::normalize(transformDirInverse({
        2 * localInter.x,
        0,
        2 * localInter.z,
    }));
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
