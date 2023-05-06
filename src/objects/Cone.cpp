/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Cone
*/

#include "objects/Cone.hpp"

Cone::Cone(Vec3 pos, Vec3 dir, float height, bool isCapped,
sf::Color color, sf::Color emmsionColor, float intensity) :
AObject(pos, color, emmsionColor, intensity)
{
    _dir = dir;
    _height = height;
    _isCapped = isCapped;
}

bool Cone::intersect(const Ray &ray, Vec3 &intersection) const
{
    Vec3 oc = ray.getOrigin() - _pos;
    float a = ray.getDir().x * ray.getDir().x - ray.getDir().y * ray.getDir().y + ray.getDir().z * ray.getDir().z;
    float b = 2 * oc.x * ray.getDir().x - 2 * oc.y * ray.getDir().y + 2 * oc.z * ray.getDir().z;
    float c = oc.x * oc.x - oc.y * oc.y + oc.z * oc.z;
    float delta = b * b - 4 * a * c;
    float t1 = (-b + sqrtf(delta)) / (2 * a);
    float t2 = (-b - sqrtf(delta)) / (2 * a);
    if (_isCapped) {
        Vec3 inter1 = ray.getOrigin() + ray.getDir() * t1;
        Vec3 inter2 = ray.getOrigin() + ray.getDir() * t2;
        Vec3 dist1 = inter1 - _pos;
        Vec3 dist2 = inter2 - _pos;
        float proj1 = Math::dot(dist1, _dir);
        float proj2 = Math::dot(dist2, _dir);
        if ((proj1 < 0 || proj1 > _height) && (proj2 < 0 || proj2 > _height))
            return false;
        if (proj1 < 0 || proj1 > _height) {
            intersection = inter2;
            return true;
        }
        if (proj2 < 0 || proj2 > _height) {
            intersection = inter1;
            return true;
        }
    }
    if (t1 < 0 && t2 < 0)
        return false;
    if (t1 < 0 || t2 < 0)
        intersection = ray.getOrigin() + ray.getDir() * (t1 < 0 ? t2 : t1);
    else
        intersection = ray.getOrigin() + ray.getDir() * (t1 < t2 ? t1 : t2);
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
