/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Cone
*/

#include "objects/Cone.hpp"

Cone::Cone(Vec3 pos, Vec3 dir, sf::Color color, sf::Color emmsionColor, float intensity) :
AObject(pos, color, emmsionColor, intensity)
{
    _dir = dir;
}

bool Cone::intersect(const Ray &ray) const
{
    Vec3 oc = ray.getOrigin() - _pos;
    float a = ray.getDir().x * ray.getDir().x - ray.getDir().y * ray.getDir().y + ray.getDir().z * ray.getDir().z;
    float b = 2 * oc.x * ray.getDir().x - 2 * oc.y * ray.getDir().y + 2 * oc.z * ray.getDir().z;
    float c = oc.x * oc.x - oc.y * oc.y + oc.z * oc.z;
    float delta = b * b - 4 * a * c;
    if (delta < 0)
        return false;
    float t1 = (-b + sqrt(delta)) / (2 * a);
    float t2 = (-b - sqrt(delta)) / (2 * a);
    if (t1 < 0 && t2 < 0)
        return false;
    return true;
}

Vec3 Cone::getIntersection(const Ray &ray) const
{
    Vec3 oc = ray.getOrigin() - _pos;
    float a = ray.getDir().x * ray.getDir().x - ray.getDir().y * ray.getDir().y + ray.getDir().z * ray.getDir().z;
    float b = 2 * oc.x * ray.getDir().x - 2 * oc.y * ray.getDir().y + 2 * oc.z * ray.getDir().z;
    float c = oc.x * oc.x - oc.y * oc.y + oc.z * oc.z;
    float delta = b * b - 4 * a * c;
    float t1 = (-b + sqrt(delta)) / (2 * a);
    float t2 = (-b - sqrt(delta)) / (2 * a);
    if (t1 < 0 && t2 < 0)
        return Vec3(0, 0, 0);
    if (t1 < 0)
        return ray.getOrigin() + ray.getDir() * t2;
    if (t2 < 0)
        return ray.getOrigin() + ray.getDir() * t1;
    if (t1 < t2)
        return ray.getOrigin() + ray.getDir() * t1;
    return ray.getOrigin() + ray.getDir() * t2;
}

Vec3 Cone::getNormal(const Vec3 &inter, unused const Ray &ray) const
{
    Vec3 normal = inter - _pos;
    normal.y = -normal.y;
    return normal;
}
